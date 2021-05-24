#include "example-program.h"

Program incrementFourBit() {
  Program program;
  
  // Set the program to have four states
  if (program.states != 0) {
    delete [] program.states;
  }
  program.stateCount = 4;
  program.states = new State [program.stateCount];

  // Create each of the four states using a for loop
  for (int i = 0; i < 4; i++) {
    Instruction onTrue; // If the current bit is true, write false, move 1 bit, and advance to the next state.
    onTrue.write = false;
    onTrue.move = 1;
    onTrue.state = i + 1;
    onTrue.halt = false;

    Instruction onFalse; // If the current bit is false, write true, move back to the start, and stop the program.
    onFalse.write = true;
    onFalse.move = -i;
    onFalse.state = 0;
    onFalse.halt = true;

    State state;
    state.onTrue = onTrue;
    state.onFalse = onFalse;

    program.states[i] = state;
  }

  return program;
}
