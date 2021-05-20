// A-Machine
// This class simulates an A-Machine, better known as the Turning Machine. It manages the flow of the program, and delegates controlling the actual hardware to an instance of the Hardware class.

#include "amachine.h"

class AMachine {
  public:
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
