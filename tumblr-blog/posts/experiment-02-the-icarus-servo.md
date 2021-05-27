# Experiment #2 : The Icarus Servo
*Experiment conducted 2021/03/02*

In this experiment I actually tried a series of things. First I tried controlling the brightness of an LED with a potentiometer. When that didn't work, I replaced the LED with a servo motor instead. At the end, I replaced the potentiometer with a photoresistor to the servo. I attached it to the arm of the servo and attempted to create a program that would make the servo move the resistor towards the brightest light reading it could find. I like to call it the [Icarus](https://en.wikipedia.org/wiki/Icarus) Servo!

# Part 1: Potentiometer Controlled LED

## How the Potentiometer Works
The potentiometer has three pins - two terminal pins and one wiper pin. The terminal pins connect to the live and ground wires. Internally, these terminals are connected to each other along a track. A wiper connects to the middle of the track, where its position along the track is rotated with the dial of the potentiometer. This essentially makes the two sides of the track variable resistors, and the whole track a potential divider circuit (whose signal can be read from the wiper pin). (If you're curious about potentiometers, [Jeff Feddersen](http://fddrsn.net/) has a clear and concise [explanation on their website](http://fddrsn.net/pcomp/examples/potentiometers.html).)

For this experiment, we can read the signal from the wiper pin into the Arduino, and then use code to output a voltage to the LED. More voltage means more light!

## Components Used
This experiment uses the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 1 x Potentiometer
* 1 x LED
* 1 x 220Ω resistor

## The Wiring
![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-02-the-icarus-servo/potentiometer-led-diagram.png)

## The Code
```cpp
void setup() {
  pinMode(7, OUTPUT); // LED ouput
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 255); // Converts the input range of the potentiometer (0-1023) to the output range of the analog pin (0-255)
  analogWrite(7, out); // Write to the LED output

  Serial.println(out);
  delay(10);
}
```

[You can see all the code for this experiment on GitHub.](https://github.com/JoshIsAStudent/physical-computing/tree/main/post-content/experiment-02-the-icarus-servo)

The code here takes the signal from the potentiometer via pin A0, and outputs the signal to the LED on pin 7. The potentiometer input is a 10-bit value (in the range 0-1023), but the output pin is only an 8-bit output (in the range 0-255). For this reason, we use the `map` function to convert the value from the input range into the output range, so that we can use the input to control the LED.

## There you have it! But not really...
I set it up in [TinkerCAD](https://www.tinkercad.com) and it worked a treat! Then I set it up my physical kit, and it didn't work.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-02-the-icarus-servo/potentiometer-led-photo.jpg)

The LED only switched between full brightness and completely off, with not even the smallest zone of "inbetween". After double checking the wiring, plotting potentiometer readings in the IDE's serial plotter, and switching out the LED for every colour in the kit, I discovered that the LEDs provided in this kit don't fade!

So let's connect it to a servo instead. Much more fun!

_Side note: It took me a moment to realise you need to assemble the potentiometer yourself. The two parts you need are in the small box with eight smaller compartments, specifically they're in the top compartment second from the right._

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-02-the-icarus-servo/little-box-photo.jpg)

# Part 2: Setting Up the Servo

## How the Servo Works
A servo motor is a particular kind of motor that, though only able to rotate in a 180°, uses a potential divider circuit to know it's position at all times. Using the Arduino we can send a target state to motor, and then it will compare the target state of the potential divider to it's actual state to determine how to drive the underlying DC motor. [_GreatScott!_](https://www.youtube.com/channel/UC6mIxFTvXkWQVEHPsEdflzQ) on YouTube has a [great video that does more in-depth](https://youtu.be/J8atdmEqZsc) on how servos work, and even how you can modify them to have more degrees of rotation.

## Components Used
This experiment uses the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 1 x Potentiometer
* 1 x Servo Motor (SG90)

## The Wiring
I removed the LED and wired up the servo instead. The brown wire connects to ground, the red to live, and the orange to our control signal from the Arduino. I used pin 9.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-02-the-icarus-servo/potentiometer-servo-diagram.png)

## The Code
I first ran example code that comes with the Ardiuno IDE to test the servo was working. You can load the example by going to `File > Examples > Servo > Sweep`. My wiring worked! I then wrote a program to use input from the potentiometer instead.

```cpp
#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(9); // Servo output
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A0); // Potentiometer input
  int out = map(val, 0, 1023, 0, 180);
  servo.write(out); // Write to the servo output

  Serial.println(val);
  delay(15);
}
```

[You can see all the code for this experiment on GitHub.](https://github.com/JoshIsAStudent/physical-computing/tree/main/post-content/experiment-02-the-icarus-servo)

Like in our LED example, I use the `map` method to translate the value from the input range to the output range, but this time the output range is 0-180, the rotations in degrees our servo can handle. The Ardiuno kindly abstracts away converting that value into the electrical signal the servo actually wants.

## There you have it! Sort of...
?[youtube](-IN2lPdBeaI)

Judging by the plot of the potentiometer signal, it seems that as the potentiometer and other components wobble about, it sends a somewhat volatile signal, hence the weird movement from the servo. Blu-tacking the potentiometer to the breadboard helped to minimise that. It worked well enough for my purposes, and I was curious to try what I've now dubbed the Icarus servo!

# Part 3: The Icarus Servo

## Components Used
This experiment uses the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 1 x Photoresistor
* 1 x 5KΩ resistor
* 1 x Servo Motor (SG90)

## The Wiring
I replaced the potentiometer with a photoresistor, in the same setup I used in my [first experiment](https://physicalcomputingwithj.tumblr.com/post/644288488002453504). To begin with, I just set it up on the breadboard, as to test that it was working. I wired the output of the potential divider to pin A0 so I could reuse the code I was currently using.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-02-the-icarus-servo/photoresistor-servo-diagram.png)

The photoresistor was not giving a huge range of values, certainly not the full 0-1023 range theoretically possible. Replacing the 10KΩ resistor I was originally using with a 5KΩ resistor helped increased the range. After that however, I just used the serial plotter to see what range of inputs the sensor was giving me, and updated my `map` function call to work in this range instead.

```cpp
int out = map(val, 10, 360, 0, 180);
```

To make my Icarus servo, I wanted to attach the photoresistor to one of the servo motor arm attachments. To ensure that the photoresistor wouldn't swing into the side of the servo, I used code to set the servo to 0 degrees, then attached the servo arm such that it would swing around the "outisde" of the servo i.e. keep clear of the blue box. I then slotted the photoresistor into the servo arm and connected it to the breadboard using plug-to-socket jumper wires.

## The Code
I wanted my servo to move the arm areas of light. My simple approach to this was to create a hill climbing algorithm. The program stores a current position in variable, and then continually rotates slightly to either side of this position to see if either of them produce a higher light reading than the current position. If they do, the current position is updated to the new one.

```cpp
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
  for (int i = -1; i <= 1; i++) { // Iterates i through the values -1, 0, 1 - corresponding to "left", "centre", and "right"
    // Calcuate next position to take a light reading from
    int testpos = pos + i * 5;
    if (testpos < 0) testpos = 0;
    if (testpos > 180) testpos = 180;

    // Move to that position
    myservo.write(testpos);
    delay(200); // The the servo time to reach it's target before taking a light reading

    // Take a light reading
    int light = analogRead(A0); // Photoresistor input

    // If that reading is the highest so far, save it and the tested position to refer to later
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

[You can see all the code for this experiment on GitHub.](https://github.com/JoshIsAStudent/physical-computing/tree/main/post-content/experiment-02-the-icarus-servo)

## There you have it! For real this time!

<iframe width="560" height="315" src="https://www.youtube.com/embed/qPuSeDbLhfQ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

[Can't see the video? Watch it on YouTube!](https://youtu.be/qPuSeDbLhfQ)

While recording the video I had my phone torch on, which I used to encourage the servo to move in particular directions. Sometimes the jumper wires would push against it, but otherwise it worked reasonably well! Working on this experiment in particular, I was surprised to see just how prevalent potential divider circuits are in electronics.

On reflection, I think part of why the movement of the servo is so janky is that each time the code pulls a signal from the photoresistor, it only takes one reading, meaning ambient variations in reading can cause the servo to move in different directions essentially at random. Taking an average reading over a few milliseconds would help prevent against this. It was definitely good insight onto how to best use the photoresistor.

The code could be also further improved by, instead of hard coding the input range from the photoresistor, dynamically setting it during runtime depending on what signals the motor receives.
