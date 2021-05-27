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
  pinMode(A0, INPUT); // Read in the 10-bit analog signal from pin A0 (x signal)
  pinMode(A1, INPUT); // Read in the 10-bit analog signal from pin A1 (y signal)

  display.shutdown(0, false); // This "wakes-up" the display, which is in power saving mode by default
  display.setIntensity(0, 8);
  display.clearDisplay(0);
}

void loop() {
  int x = 1023 - analogRead(A1); // Doing 1023 minus the singal inverts it, which I did to ensure the pupil's movement is not inverted from that of the joystick's
  int y = analogRead(A0);

  // Downscale the input range to the width/height of the matrix
  // Bitshifting the 10 bit input 7 bits to the right causes it to be 3 bits, i.e. 0-7
  x = x >> 7;
  y = y >> 7;

  // Draw the eyeball
  byte pupil = 3 << x; // 3 is 11 in binary. These bits are then shifted as far as they need to go
  for (int i = 0; i < 8; i++) {
    byte col = eyeball[i];
    if (i == y || i == y - 1) {
      col = col | pupil;
      // | is the bitwise inclusive OR operator. Each bit of it's operator is the result of ORing the corresponding bits in it's inputs
      // In essence, this combines the outline of the eyeball with the pupil
    }

    display.setColumn(0, i, col);
  }

  display.clearDisplay(0); // Clear the display
}
