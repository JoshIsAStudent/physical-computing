# Assembling the machine

* Coded up maintenance mode

## Trouble shooting servo IR problems
* Servo motor is making suttering noises, but not moving
* The IR ir receiver is constantly flashing red, as if receiving signals , but the decoded output is nonsense

* Cutting power to the servo stops the noise
* Cutting power to the receiver stops the flashing, but not the noise
* Removing the servo control wire stops the stuttering
* Removing the ir signal wire does not stop the stuttering

* First checked that the program was using the right pins
* Then switched to a different program (from my main program to the hardware test) - the issue was gone

* Back in main program
* Commented out hardware.loop - issue present
* Commented out everything - no issue
* Uncommented amachine - no issue
* Uncommented hardware, but not hardware.loop or hardware.setup - no issue
* Uncommented hardware.loop - no issue
* Uncommented hardware.stup - issue returns!
* We have found our culprit!

```cpp
void Hardware::setup() {
  Serial.begin(9600);

  pinMode(photoresistorPin, INPUT);

  pinMode(runningLedPin, OUTPUT);
  pinMode(maintenanceLedPin, OUTPUT);
  pinMode(signalLedPin, OUTPUT);

  writeMotor.attach(writeMotorPin);

  irReceiver.enableIRIn();
}
```

* Commented out last two lines - no issue
* Uncommented last line - no issue
* Re-commented that line and uncommented second to last line - no issue
* Uncommented both lines - issue returns!
* huh...

* In hardware.loop

```cpp
void Hardware::loop() {
  digitalWrite(runningLedPin, amachine->running ? HIGH : LOW );
  digitalWrite(maintenanceLedPin, maintenanceMode ? HIGH : LOW );
  handleRemote();
}
```

* Commented out handleRemote() - issue persists
* \*minecraft villager noise\*

* Tried hardcoding pin values to the correct ones - issue persists
* Tried connected the IR receiver to 3.3v instead of the 5v rail - issue persists

* I did some tampering, and even after disconnecting the live wire from the rail, and the photoresistor, the receiver, and the motor off the rail, I could still get the program to register an input from the (unplugged) ir sensor, just by touching the end of the live wire. Sometimes if would also act by itself.
* I unplugged the receiver signal wire, and plugged it in again, and it stopped
* Tried moving the receiver cable to pin 13 and the servo motor to pin 6 (so they were far part) - issue persists

* Created a simple program to see if I could truley isolate the issue to my program - issues persists!
```cpp
#include <Servo.h>
#include "IRremote.h"

Servo servo;
IRrecv ir(13);
void setup() {
  servo.attach(6);
  ir.enableIRIn();
}

void loop() {

}
```
* Disconnected everything from the main rail except the servo and connected the ir to 3.3 - issue persists
* Disconnected everything from everywhere (including the stepper motor) except the servo motor - issue persists

* With a corrected worded (internet search)[https://www.ecosia.org/search?q=arduino+ir+receiver+and+servo+motor+problem], I found this! https://forum.arduino.cc/t/irreceiver-library-servo-strange-behaviour/536118
* Turns out, the two libraries don't play nice
* The hack solution, enable the servo motor whenever we want to use it the disable it again (https://forum.arduino.cc/t/servo-twitch-with-irremote-library/129288/3)
* It works! :D

## Assembly
* Tried putting servo on metal wire - worked but wasn't in fixed position and cable was in the way
* Did current solution (cardbard on side with wire sticking out, then wrapped around servo to hold it in the air)

* Experimented with putting bit in position, spinning 360, then seeing if it was still hittable (often it wasn't)
* Also noticed motor had trouble spinning in a particular direction
* Even removing the disc - the issue remained
* After watching this video I thought of opening the motor up to see if something had gotten inside (fluff or blu tack) https://www.youtube.com/watch?v=15K9N1yVnhc
* However, once I realised I could just juggle the head up and down a few times, that's what I did, and it resolved the issue!
* Putting the disc back on, I was able to make it a tighter fit than before! (except it warbled, so I had to replace it anyway)
