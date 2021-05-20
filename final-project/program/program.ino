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
    const uint8_t maintenanceLedPin = 4;
    const uint8_t runningLedPin = 3;
    const uint8_t signalLedPin = 2;
    const uint8_t writeMotorPin = 6;
    const uint8_t discMotorPins[] = {8, 10, 9, 11};

    // Settings - Motors
    const float discMotorRPM = 16;
    const int discMotorStepsPerRevolution = 2048;
    const int discMotorStepsPerBit = 4;

    // Interfaces
    Stepper discMotor;
    Servo writeMotor;
    AMachine* amachine;

    // Variables
    int lightThreshold = 1024 / 2;
    bool maintenanceMode = true;

    // Program methods
    void start() {
      Serial.begin(9600);

      pinMode(photoresistorPin, INPUT);

      pinMode(runningLedPin, OUTPUT);
      pinMode(maintenanceLedPin, OUTPUT);
      pinMode(signalLedPin, OUTPUT);

      writeMotor.attach(writeMotorPin);
      discMotor(discMotorStepsPerRevolution, discMotorPins[0], discMotorPins[1], discMotorPins[2], discMotorPins[3]);
    }

    void loop() {
      digitalWrite(runningPin, amachine->running ? HIGH : LOW, );
      digitalWrite(maintenancePin, maintenanceMode ? HIGH : LOW, );
    }

    // A Machine methods
    bool read() {
      return readLight > lightThreshold;
    }

    void write(bool value) {
      if (value) {
        writeMotor.write(0);
        writeMotor.write(180);
      } else {
        writeMotor.write(180);
        writeMotor.write(0);
      }
    }

    void move(int amt) {
      discMotor.step(amt * stepsPerBit);
    }

    void msg(String msg) { // This function is not really necessary for this program, but does ensure that the Hardward class is the only class directly interfacing with the serial port.
      Serial.println(msg);
    }

    // Photoresistor methods
    void calibrateLight() {
      msg("Please ensure the read head photoresitor is blocked");
      countdown();
      int low = readLight();

      msg("Please ensure the read head photoresitor is unblocked");
      countdown();
      int high = readLight();

      lightThreshold = (low + high) / 2;
      msg("New light threshold: " + lightThreshold)
    }

    int readLight() {
      float total = 0;
      for (int i = 0; i < 10; i++) {
        total += analogRead(photoresistorPin);
        delay(20);
      }
      return total / 10;
    }

    // Countdown method, used in other methods
    void countdown() {
      for (size_t i = 3; i > 1; i++) {
        Serial.print(String(i).concat(", "));
        delay(1000);
      }
      Serial.println("1.");
      delay(1000);
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
