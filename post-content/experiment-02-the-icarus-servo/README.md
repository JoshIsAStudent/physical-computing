# Experiment 02: The Icarus Servo
*Experiment conducted 2021/03/02*

[In this series of experiments I:]>[This is a terrible way of laying out this information. It should be a paragraph really, I just couldn't figure out how to word it. Also, it's a different order to how I actually did it, and Ive changed by mind about how I'll actually write this, I'll write out what I actually did instead]

* Wired a servo controlled by a simple program
* Setup the servo to be controlled by a [potentiometer]>[how to spell this thing???]
* Attached a photoresistor to the servo, and attempted to create a
program that would make the servo move the resistor towards the brightest light reading it could find. I like to call it the [Icarus](https://en.wikipedia.org/wiki/Icarus) Servo!

## [Components Used]>[Incomplete list]
?[standard-components]
* 1 x LED
* 1 x 220Ω resistor
* 1 x potentiometer
* 1 x Photoresistor
*
* 4 x [X]>[How many??]Ω resistors

## Part 1: Potentiometer
First I set up the potentiometer with the intention to have it control the brightness of an LED.

The potentiometer has three PINs, two terminals and one wiper. The terminal pins connect to the live and ground wire. The wiper connects to the middle of a track connecting the two terminals, where the wiper's position along the track is rotated with the dial of the potentiometer, essentially making the two sides of the track variable resistors, and the whole potentiometer a [potential divider circuit](@post-link-potential-divier-circuit). We can read this signal from the wiper pin into the Arduino, and then use code to output a voltage to the LED. More voltage, more light!

[]>[Include a thinker CAD diagram]

```C
void setup() {
  pinMode(7, OUTPUT); // LED ouput
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 255);
  analogWrite(7, out);

  Serial.println(out);
}
```

?[complete-code](02a-potentiometer-led)

The code here takes the signal from the potentiometer via pin A0, and outputs the signal to the LED on pin 7. The potentiometer input is a 10-bit value (in the range 0-1023), but the output pin is only a 8-bit output (in the range 0-255). For this reason, we use the `map` function to convert the value from the potential from the input range into the output range, before using it to control the LED.

I set it up in [tinker CAD]>[Get the compiler to recognise when I spell this differently] and it worked a treat! Then I set up my physical kit, and it didn't work.

[]>[Include a video w/ voice over!]

(It took me a moment to realise you need to assemble the potentiometer yourself. The two parts you need are in the small box with eight smaller compartments, specifically they're in the top compartment second from the right.)

As can be seen in the video, the LED only switched between full brightness and completely off, with not even the smallest zone of "inbetween". After double checking the wiring, plotting potentiometer readings in the IDE to verify they were functioning as planned, and switching out the LED for every colour in the kit, it turns out the LEDs provided in this kit don't fade!

So let's connect it to a servo instead. Much more fun!

## Part 2: Setting Up the Servo
[]>[Maybe say what a servo is??]

I took the LED off my breadboard and wired up a servo instead. The brown wire connects to ground, the red to live, and the orange to our control signal from the Arduino. I used pin 9.

[]>[Photograph? TinkerCAD? Whichever works]

I first ran example code that comes with the Ardiuno IDE to test the servo was working. You can load the example by going to `File > Examples > Servo > Sweep`. My set up worked!

[]>[Video??]

Then I wrote a program to use input from our potentiometer instead.

```C
#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9); // Servo output
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 180);
  servo.write(out);
  Serial.println(val);
  delay(15);
}
```

?[complete-code](02b-potentiometer-servo)

Like in our LED example, I use the `map` method to translate the value from the input range to the output range, but this time the output range is 0-180, the rotations in degrees our servo can handle. The Ardiuno kindly abstracts away converting that value into the electrical signal the servo actually wants.

And then it works! Sort of?

[]>[Video]

Judging by the plot of the signal being sent from the potentiometer, it seems that as the potentiometer and other components wobble about, it sends a somewhat volatile signal, hence the weird movement from the servo. Blu-tacking the potentiometer to the breadboard [helped to minimise that]>[is it worth researching other things].

## Part 3: The Icarus Servo

### The Wiring
But now for the exciting bit! I took out the potentiometer and replaced it with a photoresistor, in the same setup I used in my [first experiment]>[link to it]. To begin with, I just set it up on the breadboard, as to test that everything was working.

[]>[tinker cad]

The photoresistor was not giving a huge range of values, certainly not the full 0-1023 range theoretically possible. Replacing the [X]>[how many also include ohms symbol] resistor with a [X]>[how many also include ohms symbol] resistor helped increased the range. After that however, I just used the serial plotter to see what range of inputs the sensor was giving me, and updated my use of the `map` method to work in this range instead.

```C
int out = map(val, 10, 360, 0, 180);
```

If doing this experiment yourself, you could use the plotter to figure out which values work best for the lighting conditions of the room you're in. Alternatively, you could have the program remember the lowest and highest reading it has received from the photoresistor, and use this as it's range.

With the photoresistor now working as desired, I decided to prepare the servo. I knew that I didn't want the wires connecting the photoresistor to hit the servo as it moved. As I had attached the servo arm attached randomly, this could have been a problem. So, I hardcoded the program to set the servo to 0 degrees, and reattached the servo arm such that the rotation of the servo would cause the arm to rotate around the "outside" of the servo i.e. keep clear of the blue box.

I then slotted the photoresistor into the servo arm, and attached it to it's original location on the breadboard using plug-to-socket jumper wires.

### The Code
I wanted my servo to move towards areas of light. My simple approach to this was to create a hill climbing algorithm. The program stores a current position in variable, and then continually rotates slightly to either side of this position to see if either of them produce a higher light reading. If they do, the position is updated to this value.

```C
#include <Servo.h>

Servo myservo;
int pos = 0;

void setup() {
  myservo.attach(9); // Servo output
  Serial.begin(9600);
}

void loop() {
  int highestLightLevel = 0;
  int newpos = pos;
  for (int i=-1; i<=1; i++) { // Iterates i through the values -1, 0, 1 - corresponding to "left", "centre", and "right"
    // Calcuate next position to take a light reading from
    int testpos = pos + i*5;
    if (testpos < 0) testpos = 0;
    if (testpos > 180) testpos = 180;

    // Move to that position
    myservo.write(testpos);
    delay(200); // The the servo time to reach it's target before taking a light reading

    // Take a light reading
    int light = analogRead(A0); // Photoresistor input

    // If that reading is the highest so far, take note of it and the tested position
    if (light > highestLightLevel) {
      highestLightLevel = light;
      newpos = testpos;
    }
  }

  // Update the "current" position of the servo to the one that produced the highest light reading
  pos = newpos;

  Serial.println(highestLightLevel);
}
```

?[complete-code](02c-the-icarus-servo)

## The Results
There was some limited success.

[]>[video]
