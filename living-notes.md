### RANDOM ###
https://www.cs.virginia.edu/~robins/Turing_Paper_1936.pdf

### UNORGANISED SCRAPS ###

# Experiments Portfolio - 4a 2021.03.09
* Try to make the video as nice as you can. Camera steady and not too short
* Include some kind of technical description - demonstrate you understand how the thing works - imagining you are explaining it to someone of your skill looking to do the same experience
* Include a circuit diagram of what you did. TinkerCAD is okay, but if you prefer a formal engineering diagram is good also.
* Include the Arduino code. Don't do a screenshot!

* Absolutely fine to recreate experiments to get extra video, you can take them further, "whatever you need to do"
* The idea is you should cover quite a breath of topics. The earlier experiments are extra useful for covering this breadth if your project focuses on something much smaller

* You are welcome to send a blog post to Anton to ask if things are okay

# Experiment - 5a 2021.03.16
* Wired LED matric according to the complete guide
* Installed LedControl library by Eberhard Fahle V1.0.6
* Used example code from lesson 15 of the egeloo zip
* It worked!

* Did experiment 1 - got the outlien of the eyeball working
* Wired the joystick, x to A0, y to A1
* Did experiment 2 - to teste the joystick
* Forgot "Serial.begin(9600);" in the startup function
* The joystick worked!
* Then I found out what I thought was x was y, (I was rotating the joystick 90deg anti-clockwise). Also the signal was inverted from what I expected

* Then I did experiment 3!
* It worked! Except I had to flip my y axis back to what it was (so now x is inverted but not y)

* I put it all together into experiment 4, and it worked!

* Experiment 5 I realised I didn't need to clear the screen after writing each column
* I had to do some funky stuff with range clamping so that the max offset of the pupils in the + direction could still be reached on values other than the joystick's absolute max. Without this, the position would flicker when the joystick was at it's extremes

* Experiment 5's code is messy, but it works

* I'm thinking I might do a tidied version where I actually organise all the axis flipping, left and right, etc

# 7a 2021.04.13
* even if you have an idea and discard it you can write a paragraph about that
* it's good to tell a story/a journey
* don't worry about deadends and failing

* electro magnets
* https://www.bbc.co.uk/bitesize/guides/z3g8d2p/revision/4
* a lot of current woudl be needed to get a strong enough electro magnet
* magnetnetic leviation

* lazy susan - rotation disk
* "friction drive might be enough"

# Anton feedback - 8a 2021.04.20
Mention explictly the angalogue to digital converter at the end of step 1


for final project, you can do one larger technical write up at the end, rather than all along the way
final project
* w/ regards to turning, it doesn't need to go very fast
* the little steper motor anton reckons will be powerful enough
* rather than having it in the centre - meaning you have to balance the disk, you could just do a frction drive, where you drive a small wheel, and then friction drive the big wheel
* the dc motor would be faster, but you would need some other way of detecting position

* I could repurpose a marble part
* Youd could also do stuff with copper wire

# Final project - 10a 2021.05.04
* Heat metal skewer
* Make hole in middle
* Attach stepper motor to hole using blu tac
* Secure stepper motor through holes in wings

# 8a 2021.04.20
Photo transistors can be more sensitive than photo resistors, and can also respond to particular wavelengths of light

# Wiring the board - 2021.05.18 12a PC notes
voltage (potential) is always relative to some arbitrary agreed zero - 0V, or "ground". So to use both the Arduino and DC power supplies, all that is required is to make sure the ground side is connected together, so it is shared as a common 0V reference. Then there will be two 5V rails (best not to connect these together directly) and components can be powered from either one.

### UNORGANISED EXPERIMENT NOTES ###

# Physical circuits - 2a 2021.02.23

## Set up serial info
* Open up the Arduino IDE
* Connect your Arduino
* Tools > Board > Arduino Uno
* Tools > Port > COM4 (Arduino Uno)
* Use Tools > Get Board Info to check that things are connected

## Notes
* Cathode is negative, anode is positive
* Cathode is short, anode is long
* If you have multiple LEDs, you probably need to give them each their own resistor

* If we hook up a variable resistor, it won't affect the voltage of the circuit, only the current
* However if you connect Input > Resitor > * > Variable resistor > Ground, and measure voltage at the point *, the voltage will change
* The stronger each resistor, the bigger "share" of the voltage it gets
* V_out = V_in * R_1/(R_1+R_2)
* If you want to read an anologue voltage input, you can do that using the alalog pins on the Arduino!

* If you only output numbers to the serial output, you can get a graph!

## Light resistor demo
```C
void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600); // You can treat this as a "magic number"
}

void loop() {
  int light = analogueRead(A0);
  Serial.println(light);
  delay(10);
}
```

# Notes - 3a 2021.03.02

## Potentiometer
* Has terminal 1, washer, terminal 2
* The terminals connect to either end of a track
* The wiper connects at some point inbetween

* You connect voltage to the terminals, and take a signal off of the washer
* Fun fact: doesn't matter which way around you connect the terminals

* 200 Ohms is fine for a LED resitor

## Anton on calculating resistance
can work it out like this: LED typically drops about 2V, precise value can be obtained from datasheet for critical work
LED current is about 20mA, again from datasheet
power supply is 5V
so with 5V - 2V = 3V across the resistor, we want it to conduct 20mA
Ohms law: R = V / I
= 3 / 0.02
= 150 Ohms, which is typical for a 5mm LED
but not critical

## Servos
* Servo's don't spin like motors, they rotate in between two angles, and you can choose the position in-between them you want to go
* It uses a potentiometer to know exactly what position it's pointing in at the moment, and uses that to try and change it's direction to the one you want
* There is a protocol for sending the desired angle to the servo along it's singal wire. We don't have to worry about this, as the Ardiuno has libraries for handling this.
  * tl;dr, the length of the pulse dictates the size of the angle
* It's a closed loop system, as it acts on feedback (it continually makes motion depending on the difference between the desired state and the actual state)

If you had problems, troubleshooted to get something working, than found a solution, that's really good to write about

# Notes - 4a 2021.03.09

## Stepper motors
* An EggBot is a good potential project

### How they work
* Idea is you run a current through a coil which creates a magnetic feild, which pushes/pulls a magenet, which causes the motor to turn
* In the case of a stepper motor, you control the current through the various coils in the motor (via software) to achieve the desired result
  * The Elegoo kit on minerva provides more of a guide
* On a DC motor you apply power and it spins, on a stepper motor, you send currents to change it's position by one "step" (a fraction of a revolution)
* In a stepper motor, you don't have absolute positioning like a servo (though you can use limit switches to figure out things like this), but you can make very precise movements

* There are bi-polar and uni-polar stepper motors. Uni-polor has a more complicated internal arrangement, but is easier to drive than the bi-polar, which is harder to drive.

* Red wire - ground
* Blue, yellow, pink, orange - control (set in software, according to sequence that are )

* As Arduino is not powerful enough to drive the motor, so we use to control a transistor, which when enabled lets a much more powerful signal through
* We do this using a ULM driver chip (I think that's what it was called), which has 8 transistors in it

## Power supply
* On the power supply, one side is 3.3V, one is 5V. You want the 5V side
  * Though you can move the jumpers about to change this
