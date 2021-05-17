// Program data structure. Stores programs that can be executed by the A-Machine.
struct Program {
  std::string name;
  std::vector<State> states;
};

struct State {
  Instruction onTrue;
  Instruction onFalse;
};

struct Instruction {
  bool halt;
  bool write;
  int move;
  int state;
};

// A-Machine - This class simulates an A-Machine, better known as the Turning Machine. It manages the flow of the program, and delegates controlling the actual hardware to an instance of the Hardware class.
class AMachine {
public:
  size_t state = 0;
  bool running = false;
  Program program;
  Hardware* hardware;

  void step() {
    if (!machine.running) {
      return;
    }

    if (state >= p->states.size()) {
      halt(“Invalid state”);
      return;
    }

    bool bit = hardware->read();
    Instruction ins = bit ?
    program.states[state].onTrue :
    program.states[state].onFalse;

    if (ins.halt) {
      halt(“Ended successfully”);
      return;
    }

    if (bit != ins.write) {
      hardware->write(ins.write);
    }

    hardware->move(ins.move);

    state = ins.state;
  }

  void halt(std::string msg) {
    running = false;
    hardware->msg(“Machine stopped in state #” + state + “ (“ + msg + “)”;
  }

}

// Hardware - This class controls all of the Arduino hardware. This includes that used by the A-Machine, as well as that used for maintenance mode.
class Hardware {
public:
  // Settings
  photoresistorPin;

  runningLedPin;
  maintenanceLedPin;
  signalLedPin;
  discMotorPins;
  writeMotorPins;

  int stepsPerBit = 4;
  float motorSpeed = 15;

  // Interfaces
  serial;
  discMotor;
  writeMotor;
  AMachine* amachine;

  // Variables
  int lightThreshold;
  bool maintenanceMode = false;

  void start() {
    // set up all the interfaces
    calibrate()
  }

  void calibrate() {
    // ask for no block, wait signal, read over time, ask for block, wait signal, read over time
    lightThreshold = (low+high)/2;
  }

  void loop() {
    digitalWrite(amachine->running?HIGH:LOW, runningPin);
    digitalWrite(maintenanceMode?HIGH:LOW, maintenancePin);
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
    discMotor.rotate(amt*stepsPerBit);
  }

  void msg(std::string msg) {
    // output to serial port
  }

}

// Main program
AMachine amachine;
Hardware hardware;

void start() {
  amachine.hardware = &hardware;
  hardware.amachine = &amachine;
  hardware.start();
}

void loop() {
  machine.step();
  hardware.loop();
}
