// Include the libraries we will need. These libraries handle some of the complex parts of controlling the eltronics for us, so we don't have to!
#include <Servo.h>
#include <Stepper.h>

// Program data structure
// Stores programs that can be executed by the A-Machine.
struct Instruction { // The series of actions the A-Machine should take on a given step
  bool halt;  // If true, the A-Machine will stop running
  bool write; // Wheter it should write true or false to the current bit
  int move;   // How many bits along it should move. Positive values move one way, negative values move the other way, zero means don't move.
  int state;  // Which number state in the program the A-Machine should switch to.
};

struct State {
  Instruction onTrue;  // The instruction that should be run when the current bit is true
  Instruction onFalse; // The instruction that should be run when the current bit is false
};

struct Program {
  State* states; // Note to self, this stackoverflow question explains how to do dynamically sized arrays in C++ https://arduino.stackexchange.com/questions/3774/how-can-i-declare-an-array-of-variable-size-globally
  int stateCount;
  String name;
};

// Forward Declarations
// Note to self: Move these classess into seperate files
class AMachine;
class Hardware {
  public:
    void start();
    void calibrate();
    void loop();
    bool read();
    void write(bool value);
    void move(int amt);
    void msg(String msg);
};

// A-Machine
// This class simulates an A-Machine, better known as the Turning Machine. It manages the flow of the program, and delegates controlling the actual hardware to an instance of the Hardware class.
class AMachine {
  public:
    size_t state = 0;
    bool running = false;
    Program program;
    Hardware* hardware;

    void step() {
      if (!running) {
        return;
      }

      if (state >= program.stateCount) {
        halt("Invalid state");
        return;
      }

      bool bit = hardware->read();
      Instruction ins = bit ?
                        program.states[state].onTrue :
                        program.states[state].onFalse;

      if (ins.halt) {
        halt("Ended successfully");
        return;
      }

      if (bit != ins.write) {
        hardware->write(ins.write);
      }

      hardware->move(ins.move);

      state = ins.state;
    }

    void halt(String msg) {
      running = false;
      hardware->msg("Machine stopped in state #" + state + " (" + msg + ")";
    }

};

// Hardware
// This class controls all of the Arduino hardware and electronics. This includes that used by the A-Machine, as well as that used for maintenance mode.
class Hardware {
  public:
    // Settings - Input pins
    const uint8_t photoresistorPin = A0;

    // Settings - Output pins
    const uint8_t runningLedPin = 1;
    const uint8_t maintenanceLedPin = 2;
    const uint8_t signalLedPin = 3;
    const uint8_t writeMotorPin = 6;
    const uint8_t discMotorPins[] = {8, 9, 10, 11};

    // Settings - Motors
    const float discMotorRPM = 16;
    const int discMotorStepsPerRevolution = 2048;
    const int discMotorStepsPerBit = 4;

    // Interfaces
    Stepper discMotor;
    Servo writeMotor;
    AMachine* amachine;

    // Variables
    int lightThreshold;
    bool maintenanceMode = true;

    void start() {
      Serial.begin(9600);

      pinMode(photoresistorPin, INPUT);

      pinMode(runningLedPin, OUTPUT);
      pinMode(maintenanceLedPin, OUTPUT);
      pinMode(signalLedPin, OUTPUT);

      writeMotor.attach(writeMotorPin);
      discMotor(discMotorStepsPerRevolution, discMotorPins[0], discMotorPins[1], discMotorPins[2], discMotorPins[3]);

      calibrate()
    }

    void calibrate() {
      // ask for no block, wait signal, read over time, ask for block, wait signal, read over time
      lightThreshold = (low + high) / 2;
    }

    void loop() {
      digitalWrite(amachine->running ? HIGH : LOW, runningPin);
      digitalWrite(maintenanceMode ? HIGH : LOW, maintenancePin);
    }

    bool read() {
      // compare light reading to calibrated values
    }

    void write(bool value) {
      if (value) {
        writeMotor.rotate(writeMotorPositionA);
        writeMotor.rotate(writeMotorPositionB);
      } else {
        writeMotor.rotate(writeMotorPositionB);
        writeMotor.rotate(writeMotorPositionA);
      }
    }

    void move(int amt) {
      discMotor.rotate(amt * stepsPerBit);
    }

    void msg(String msg) { // This function is not really necessary for this program, but I created it so that other parts of the code besides the Hardware class weren't interacting with the serial port directly.
      Serial.println(msg);
    }

};

// Main program
AMachine amachine;
Hardware hardware;

void start() {
  amachine.hardware = &hardware;
  hardware.amachine = &amachine;
  hardware.start();
}

void loop() {
  hardware.loop();
  if (!hardware.maintenanceMode) amachine.step();
}
