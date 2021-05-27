#include "LedControl.h" // LedControl library by Eberhard Fahle V1.0.6.
LedControl display = LedControl(12, 10, 11, 1); // Connect to DataIn, CS, and CLK respectively

// An array of bytes, where each byte corresponds to a column, and each bit to an LED
// The array is constant as it stores the static parts of the eyeball
const byte eyeball[8] = {
  B00111100,
  B01000010,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B01000010,
  B00111100,
};

void setup() {
  display.shutdown(0, false); // This "wakes-up" the display, which is in power saving mode by default
  display.setIntensity(0, 8);
  display.clearDisplay(0);
}

void loop() {
  for (int col = 0; col < 8; col++) {
    display.setColumn(0, col, eyeball[col]);
  }
  delay(1000); // These delays are just in place for testing
  display.clearDisplay(0);
  delay(1000);
}
