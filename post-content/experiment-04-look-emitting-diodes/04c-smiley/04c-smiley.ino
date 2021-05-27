#include "LedControl.h" // LedControl library by Eberhard Fahle V1.0.6.
LedControl display = LedControl(12, 10, 11, 1); // Connect to DataIn, CS, and CLK respectively

void setup() {
  pinMode(A0, INPUT); // Read in the 10-bit analog signal from pin A0 (x signal)
  pinMode(A1, INPUT); // Read in the 10-bit analog signal from pin A1 (y signal)

  display.shutdown(0, false); // This "wakes-up" the display, which is in power saving mode by default
  display.setIntensity(0, 8);
  display.clearDisplay(0);
}

void loop() {
  int x = analogRead(A1);
  int y = 1023 - analogRead(A0); // Doing 1023 minus the singal inverts it, which I did to ensure the pupil's movement is not inverted from that of the joystick's

  // Map the positions to the range of the display, and also clamp the positions
  x = map(x, 0, 1023, -3, 3 + 1);
  y = map(y, 0, 1023, -7, 1 + 1);
  x = min(x, 3);
  y = min(y, 1);

  // Determine the position of the eyes
  int top = 6 + y;
  int left = 2 + x; // (the x axis is 0 at the right side of the matrix from my perspective)
  int right = 5 + x;

  // Clamp the positions
  right = constrain(right, 2, 7); // These are likely muddled up!
  left = constrain(left, 0, 5);

  // Draw the eyes
  for (int i = 0; i < 8; i++) {
    byte row = 0;
    if (i == left || i == right) {
      row = B111 << top - 1;
    }

    display.setRow(0, i, row); // Now we are drawing rows, not columns, as that made the most sense for the new vertical lines for eyes
  }
}
