// A-Machine
// This class simulates an A-Machine, better known as the Turning Machine. It manages the flow of the program, and delegates controlling the actual hardware to an instance of the Hardware class.

#ifndef AMACHINE_H
#define AMACHINE_H

#include "program.h"
class Hardware; // Forward declaration of Hardware class so that we can create a pointer to it. If we included it instead, `machine.h` and `hardware.h` would have cyclic include dependicies

class AMachine {
  public:
    size_t state = 0;
    bool running = false;
    Program program;
    Hardware* hardware;

    void step();
    void halt(String msg);
};

#endif
