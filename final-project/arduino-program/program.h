// A-Machine program data structure //
// Stores programs that can be executed by the A-Machine.

#ifndef PROGRAM_H
#define PROGRAM_H

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
  State* states;
  int stateCount;
};

#endif
