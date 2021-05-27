#include "amachine.h"

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
