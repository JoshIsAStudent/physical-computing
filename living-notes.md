### RANDOM ###
* https://www.cs.virginia.edu/~robins/Turing_Paper_1936.pdf

### CONTENT TO INCLUDE/COVER ###

# General
* De-clog motor but moving axle in and out
* Talk about how the light sensor takes a reading over time
* Talk about separation of amachine and hardware in final program

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

# Wiring the board - 2021.05.18 12a PC notes
voltage (potential) is always relative to some arbitrary agreed zero - 0V, or "ground". So to use both the Arduino and DC power supplies, all that is required is to make sure the ground side is connected together, so it is shared as a common 0V reference. Then there will be two 5V rails (best not to connect these together directly) and components can be powered from either one.


### ADVICE ###
* Try to make the video as nice as you can. Camera steady and not too short.
* Include some kind of technical description - demonstrate you understand how the thing works - imagining you are explaining it to someone of your skill looking to do the same experience.
* Include a circuit diagram of what you did.

* The idea is you should cover quite a breath of topics. The earlier experiments are extra useful for covering this breadth if your project focuses on something much smaller

# Anton feedback - 8a 2021.04.20
* for final project, you can do one larger technical write up at the end, rather than all along the way
final project


### EARLY EXPERIMENTS ###

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

# Notes - 3a 2021.03.02

## Potentiometer
* Fun fact: doesn't matter which way around you connect the terminals

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
