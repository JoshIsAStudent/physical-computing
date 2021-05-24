#include "amachine.h"

void AMachine::step() {
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

  if (bit != ins.write) {
    hardware->write(ins.write);
  }

  hardware->move(ins.move);

  state = ins.state;

  if (ins.halt) {
    halt("Ended successfully");
    return;
  }
}

void AMachine::halt(String msg) {
  running = false;
  String m("Machine stopped in state #");
  m += state;
  m += " (";
  m += msg;
  m += ")";
  hardware->msg(m);
}
