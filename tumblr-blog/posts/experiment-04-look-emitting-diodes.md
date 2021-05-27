# Experiment #4 : Look Emitting Diodes
*Experiment conducted 2021/03/16*

I decided to have a look at the components provided in the kit and see which might be fun in combination. I saw the joystick and 8x8 led matrix display, and thought it might be fun to make something that moves around on the screen depending on the joystick input. As I made the screen display a face you can make look in different directions, I've dubbed them the "Look Emitting Diodes"!

# Components Used
This experiment uses the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 1x 8x8 LED Dot Matrix Display (MAX7219)
* 1x Joystick

# Part 1: Wiring the Display

## The Wiring
I first connected the 8x8 matrix display as shown. n.b. TinkerCAD doesn't have an LED matrix or a joystick, so I created both in MS Paint.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-04-look-emitting-diodes/display-diagram.png)

To be able to control the display from the Arduino, I installed the LedControl library by Eberhard Fahle V1.0.6. I ran the example code from lesson 15 of the Elegoo starter kit PDF to verify that the display was working!

## The Code
To see how I could write my own output to the display, I wrote a program that displayed the static outline of my eyeball, with intention to add the moving pupil next.

At the start of the program, we include the `LedControl` library and initialise an interface to our display.

```cpp
#include "LedControl.h" // LedControl library by Eberhard Fahle V1.0.6.
LedControl display = LedControl(12, 10, 11, 1); // Connect to DataIn, CS, and CLK respectively
```

Next, I create a constant array of bytes, which I essentially treat as an 8x8 2D array of bits. In C++, putting a `B` before a sequence of ones and zeros creates a byte literal, meaning the language will interpret the numbers as binary, and not base 10.

```cpp
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
```

In the `setup` function, we prepare the display for showing our output. Most notably, we have to wake up the display from power saving mode.

```cpp
void setup() {
  display.shutdown(0, false); // This "wakes-up" the display, which is in power saving mode by default
  display.setIntensity(0, 8);
  display.clearDisplay(0);
}
```

In the loop function then, we literate over each byte in the array, and write it to the corresponding column in the display. Thankfully, the library handles the complexity of this for us!
```cpp
void loop() {
  for (int col = 0; col < 8; col++) {
    display.setColumn(0, col, eyeball[col]);
  }
  delay(1000); // These delays are just in place for testing
  display.clearDisplay(0);
  delay(1000);
}
```

[You can view the complete code on GitHub.]()

# Part 2: Completing the Eyeball

## The Wiring
Next I wired the joystick, which was pretty straightforward. I didn't wire up the switch pin and I wasn't using it for this experiment, though I suppose I could have rigged it up to trigger a blink animation. Throughout the experiment I kept switching which wire I treated as the "x" input and which as the "y" as I kept holding the joystick at different angles.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-04-look-emitting-diodes/joystick-diagram.png)

## The Code
To be able to read in from the joystick I updated my setup function.

```cpp
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); // Read in the 10-bit analog signal from pin A0 (x signal)
  pinMode(A1, INPUT); // Read in the 10-bit analog signal from pin A1 (y signal)

  display.shutdown(0, false); // This "wakes-up" the display, which is in power saving mode by default
  display.setIntensity(0, 8);
  display.clearDisplay(0);
}
```

The real magic of drawing the moving pupil then I do in the loop function, predominately through the use of bit operators.

```cpp
void loop() {
  int x = 1023 - analogRead(A1); // Doing 1023 minus the singal inverts it, which I did to ensure the pupil's vertical movement is not inverted from that of the joystick's
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
```

With the exception of some odd behaviour around the edges, it worked well!

[You can view the complete code on GitHub.]()

# Part 3: A New Face in Town
Now the experiment was working, I decided a single eyeball was a little creepy, and wanted to replace it with a face that had two eyes. This worked in largely the same way as before, but I added some additional logic to make the eyes move closer together as the user moves up against the edge of the display. As each eye is just a line, I do this by clamping the x position of each eye to be within certain bounds. Though, this code got a little messy as I tried to find ways to let the user reach the edge of the display without having to push the joystick absolutely as far as it could go.

When writing my new code, I also realised that I didn't need to clear the display on each loop. This is because when the library writes each byte, it still writes the zeros, essentially clearing anything that was there before.

This is the loop function of the new code.

```cpp
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
```

[You can view the complete code on GitHub.]()

# Hello World!

I think the end result is pretty charming! It was definitely an interesting application of binary bit manipulations and helped me practise my skills in using them. Though, the final code could definitely be un-muddled and improved. I definitely learned more about what to be thinking about when interpreting input signals from electronics in non-continuous ways - dealing with nuances such as ensuring the absolute maximum value of the input signal does not have it's own discrete output value.
