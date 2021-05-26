# Experiment #3 : Stepper Motors
*Experiment conducted 2021/03/09*

In this experiment I made an attempt at setting up the 28BYJ-48 stepper motor. Though I couldn't get it to work in this experiment, I was able to connect a working version in my final project.

## How The Stepper Motor Works
Stepper motors come in bi-polar and uni-polar variants. The 28BYJ-48 motor is uni-polar. Compared to bi-polar stepper motors, uni-polar motors have a more complicated internal arrangement but with the tradeoff that they are easier to drive.

Inside the motor there are two metal coils surrounding a rotating magnet, where each coil is associated with two sets of metal teeth that also surround the magnet. Running current through each coil in one direction or the other creates an electromagnetic field, where the direction of the field affects how the teeth are magnetised. By controlling the flow of current through the coils in a particular way, it is possible to rotate the magnet by repeatedly attracting it to one set of teeth after another. This is how the stepper motor is able to rotate with precise control over the speed, length, and direction of the rotation, as opposed to a DC motor which rotates more freely. Stepper motors don't have absolute positioning like a servo does, though limit switches can be used to determine when the motor has rotated a particular point.

The Arduino itself cannot supply sufficient power to the stepper motor. Instead, a stronger power supply is fed into the driver board, and the Arduino controls transistors on the board, which when enabled allow the stronger power supply to pass into the motor. Though this isn't literally what happens, the effect is that the four outputs from the Arduino are amplified by the driver board. Of the five wires connecting to the motor, one is the live wire, which connects to the centre of both motors. Each coil then has one wire attached at either end, which makes up the remaining four wires. By changing which of these four wires are connected to ground, it is possible to control the flow of current through each coil. The red LEDs on the driver board show which control wires are currently live. In order for the driver board to work when connected to the Arduino, the Arduino and the driver board should share a common ground.

If you're looking for complete information on the motor [Bret Stateham](http://Bret​Stateham.com) has a great [video on YouTube](https://youtu.be/B86nqDRskVU) explaining how it operates.

# Components Used
This experiment uses the Arduino UNO R3 Project Starter Kit.

* 1 x UNO R3 Controller Board (the Arduino)
* 1 x Breadboard
* Breadboard jumper wires
* 1x Stepper Motor (28BYJ-48)
* 1x Stepper Motor Driver Board (ULN2003)
* 1x Power supply module

# Wiring the Stepper Motor
Below is a diagram showing how I wired the stepper motor. n.b. [TinkerCAD](www.tinkercad.com) doesn't include a stepper motor and  driver board in it's available components, so I've recreated the driver board using a mini breadboard. Additionally, the power supply is different to that provided in the kit.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-03-stepper-motors/wire-stepper.png)

In essence, the four control pins on the driver board (from top to bottom, as pictured below) connect to pins 11 through 8 on the Arduino (in that order). You could use other pins, these were just those used by the example programs I was trying to run. The live connection from the power supply is run through the breadboard and then into the driver board. Though the breadboard could be made redundant in this example, using it made it easy to connect all the grounds connections of the Arduino, the motor, and the power supply, as to have a shared connection.

When attaching the power supply supplied in the kit, be sure to connect it such that the plus and minus icons denoted on the output pins connect into the correct rails on the bread board. (I initially got this wrong.) With this power supply you can provide power either by using a wall socket plug or by using a battery, as pictured below. Make sure also the jumper on the power supply unit is set to output 5V - as the stepper motor requires this.

![](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/experiment-03-stepper-motors/battery-photo.jpg)

Unfortunately, I couldn't get this working and I was never able to identify why. I even tried replacing the chip on the driver board with what *I thought* were spare chips provided in the kit. In actuality however, these are entirely different chips, and not interchangeable at all. Later on in my final project, I was able to get the stepper motor working, and so my suspicion is that there was an issue with the code I was trying to run - particularly as I ran into such issues during my final project.
