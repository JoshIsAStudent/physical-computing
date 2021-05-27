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
