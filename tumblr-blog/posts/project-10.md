# Final Project #10 : Technical Breakdown
_Alternative title: So you want to build a Turning Machine?_

This post breaks down the electrical components and wiring of the final machine I made, and also gives a high level overview how I made the Arduino program.

# Components
For this project I used the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 3 x LEDs (of any colour, but preferably each a different colour)
* 1 x Red or Green LED
* 4 x 220Ω resistor
* 1 x Photoresistor
* 1 x 5KΩ resistor
* 1 x Stepper Motor (28BYJ-48)
* 1 x Stepper Motor Driver Board (ULN2003)
* 1 x Power supply module
* 1 x Servo Motor (SG90)
* 1 x IR receiver module
* 1 x IR remote

# Wiring

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/project-10/wiring-diagram.jpg)

# The code
[You can see the complete code on GitHub.](https://github.com/JoshIsAStudent/physical-computing/tree/main/final-project/arduino-program)

The code is separated into two core classes, `AMachine` and `Hardware`. This [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns) made it much easier for me to work on the project. Had the two functions been conflated, it would have been trickier to tell whether errors were due to issues with my hardware code or due to my turning machine implementation.

As these classes handle almost all of the program's complexity, the main [`.ino` filb.](https://github.com/JoshIsAStudent/physical-computing/blob/main/final-project/arduino-program/arduino-program.ino) is actually quite straightforward.

```cpp
#include "hardware.h"
#include "amachine.h"
#include "example-program.h"

// Variables
AMachine amachine;
Hardware hardware;

// Setup - Is run once by the Arduino
void setup() {
  amachine.program = incrementFourBit();
  amachine.hardware = &hardware;
  hardware.amachine = &amachine;
  hardware.setup();
}

// Loop - Is run repeatedly by the Arduino
void loop() {
  hardware.loop();
  if (!hardware.maintenanceMode) amachine.step();
}
```

## The A-machine Class
The a-machine class emulates the Turning machine, and I implemented in such a way to try and be as abstract as possible. For this reason, it has no direct control over the electronics. Instead, it has a pointer to a `Hardware` object, which is uses as an interface to the hardware. The declaration for the class summarises it quite well.

```cpp
class AMachine {
  public:
    size_t state = 0;
    bool running = false;
    Program program;
    Hardware* hardware;

    void step();
    void halt(String msg);
};
```

It's attributes store the state of the machine, whether or not is it currently running, and what program it is executing (more on that below). The class only has two methods, `step` and `halt`. The `step` method is the heart of the machine, and is run every time the Arduino loops. Even without comments, it is pretty easy to understand.

```cpp
void AMachine::step() {
  if (!running) { // If the machine isn't running, don't step
    return;
  }

  if (state >= program.stateCount) { // If the program doesn't contain instructions for the state we are in, halt the machine
    halt("Invalid state");
    return;
  }

  bool bit = hardware->read(); // Read the current bit, and select which instruction to execute accordingly
  Instruction ins = bit ?
                    program.states[state].onTrue :
                    program.states[state].onFalse;

  if (bit != ins.write) { // ins.write dicates *what* should be written to the bit (not *if* we should write or not)
    hardware->write(ins.write);
  }

  hardware->move(ins.move); // move as many bits as the instruction dicates, where positive numbers go one way, and negative numbers the other

  state = ins.state; // Advance the machine to the next state

  if (ins.halt) { // Halt the machine if the program tells us to
    halt("Ended successfully");
    return;
  }
}
```

The `halt` method could be replaced with `running = false; state = 0;` in every instance, but as it was also helpful to output debug information to the serial monitor while testing, I turned it into it's own utility method.

```cpp
void AMachine::halt(String msg) {
  String m("Machine stopped in state #");
  m += state;
  m += " (";
  m += msg;
  m += ")";
  hardware->msg(m);

  running = false;
  state = 0;
}
```

## The Hardware Class
The `Hardware` class handles all of the machine's electronics and serial communication. It's primary methods are `read`, `write`, `move`, and `msg`, as they are all used by the `AMachine` to interface with the hardware. It also has `setup` and `loop` methods, called by their respective Arduino functions, that are responsible for initialising the hardware, updating the status LEDs, and responding to input from the IR receiver. All additional methods are essentially utility methods used in service of the others.

Of note, having learned by lesson from a [previous experiment](https://physicalcomputingwithj.tumblr.com/post/652206318924496896), is that the `read` method will take an average reading from the photoresistor over a short time period, to help mitigate the effects of noise in the signal.

[You can see the code for this class on GitHub in the `hardware.h` and `hardware.info` files.](https://github.com/JoshIsAStudent/physical-computing/tree/main/final-project/arduino-program)

Keeping the `AMachine` and `Hardware` classes separate worked out well for me when implementing the failure-to-write failsafe. As this is distinctly a hardware problem, I was able to update the `Hardware::write()` method to keep checking if the bit had been written to, without having to alter or complicate the Turning machine implementation at all.

**Hardware::write() in hardware.ino**
```cpp
void Hardware::write(bool value) {
  msg(String("Writing ") + (value ? "TRUE" : "FALSE"));
  writeMotor.attach(writeMotorPin);

  bool realValue = !value;
  while (realValue != value) {
    writeMotor.write(writeMotor.read() == 0 ? 180 : 0);
    delay(800);
    realValue = read();
  }

  writeMotor.detach();
}
```

**Writing in AMachine::step() in amachine.ino**
```cpp
if (bit != ins.write) {
  hardware->write(ins.write);
}
```

Another nice benefit of separating the hardware code from the turning machine code, is that the hardware code could be completely reworked for a different set-up, and the `AMachine` class would still be able to operate it so long as it had the primary methods required. For this project I didn't implement a C++ interface as it wasn't needed, but had I have done it would have looked something like this.

```cpp
class HardwareInterface {
public:
  bool maintenanceMode

  // Program methods
  virtual void setup() = 0;
  virtual void loop() = 0;

  // A Machine methods
  virtual bool read() = 0;
  virtual void write(bool value) = 0;
  virtual void move(int amt) = 0;
  virtual void msg(String msg) = 0;
};
```

With only some minor tweaks the rest of the program would work with any class that implemented this interface. (You could even implement a virtual hardware if you wanted to!)

## The Program Structure
The final piece of the puzzle is how we represent programs that the Turning machine can execute, which in the sprit of [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns) is separate from the Turning Machine implementation itself. (It also just makes it a lot easier to swap out which program the Turning Machine is running.) Like the Turning machine's `step` method, the code is reasonably self explanatory. As it's a simple data structure, it fits entirely in a header file, no implementation file required!

```cpp
struct Instruction { // The series of actions the A-Machine should take on a given step
  bool write; // Wheter it should write true or false to the current bit
  int move;   // How many bits along it should move. Positive values move one way, negative values move the other way, zero means don't move.
  int state;  // Which number state in the program the A-Machine should switch to.
  bool halt;  // If true, the A-Machine will stop running
};

struct State {
  Instruction onTrue;  // The instruction that should be run when the current bit is true
  Instruction onFalse; // The instruction that should be run when the current bit is false
};

struct Program {
  State* states; // An array of states
  int stateCount;
};
```

It wasn't really necessary for this project to be able to serialise and read back `Program` data structures, so the example program I ran in the demos is just hard coded in [`example-program.cppb.](https://github.com/JoshIsAStudent/physical-computing/blob/main/final-project/arduino-program/example-program.cpp).

This is the program it generates. It is able to increment a 4-bit number by one, and then return to the memory cell where it started.

| State | If    | Write | Move | Next State | Halt  |
| ----- | ----- | ----- | ---- | ---------- | ----- |
| **0** | TRUE  | FALSE | 1    | 1          | FALSE |
|       | FALSE | TRUE  | 0    | 0          | TRUE  |
| **1** | TRUE  | FALSE | 1    | 2          | FALSE |
|       | FALSE | TRUE  | -1   | 0          | TRUE  |
| **2** | TRUE  | FALSE | 1    | 3          | FALSE |
|       | FALSE | TRUE  | -2   | 0          | TRUE  |
| **3** | TRUE  | FALSE | 1    | 4          | FALSE |
|       | FALSE | TRUE  | -3   | 0          | TRUE  |

n.b. if you didn't want it to be able to return to where it started, you only actually need one state. This program can increment a binary number of any size.

| State | If    | Write | Move | Next State | Halt  |
| ----- | ----- | ----- | ---- | ---------- | ----- |
| **0** | TRUE  | FALSE | 1    | 0          | FALSE |
|       | FALSE | TRUE  | 0    | 0          | TRUE  |
