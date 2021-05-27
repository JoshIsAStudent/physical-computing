# Final Project #7 : Assembly of the Components

Now that I had each part of the machine working in isolation (save for the perils of the memory disc), it was time to put them all together! A complete technical breakdown of the machine is included at the end of the blog, but this post outlines the particular challenges I faced.


## Testing the Hardware
My first step was to connect all of the components to the Arduino and appropriate power supply. Save for the handful of challenges outlined below, the components all worked as expected! I initially tested the components using a [simple program](https://github.com/JoshIsAStudent/physical-computing/blob/main/final-project/hardware-test/hardware-test.ino) that would iterate through each component and operate it. (I even reused my decode function from my photoresistor decoder to test the LEDs.)

```cpp
#include <Stepper.h>
#include <Servo.h>

// Stepper motor
const int stepperStepsPerRevolution = 2048;
const int stepperRPM = 15;
Stepper myStepper(stepperStepsPerRevolution, 8, 10, 9, 11);

// Servo motor
const uint8_t writeMotorPin = 6;
Servo myServo;

// Pins
const uint8_t photoresistorPin = A5;
const uint8_t maintenanceLedPin = 4;
const uint8_t runningLedPin = 3;
const uint8_t signalLedPin = 2;

// Program
bool decode(int x, int k) {
  return (x & (1 << k)) != 0;
}

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(stepperRPM);
  myServo.attach(writeMotorPin);
  pinMode(photoresistorPin, INPUT);
  pinMode(maintenanceLedPin, OUTPUT);
  pinMode(runningLedPin, OUTPUT);
  pinMode(signalLedPin, OUTPUT);
}

void loop() {
  // Stepper Motor
  if (true) {
    Serial.println("Stepper clockwise");
    myStepper.step(stepperStepsPerRevolution);
    delay(1000);
    Serial.println("Stepper counterclockwise");
    myStepper.step(-stepperStepsPerRevolution);
    delay(1000);
  }

  // Servo motor
  if (true) {
    Serial.println("Servo 180");
    myServo.write(180);
    delay(1000);
    Serial.println("Servo 0");
    myServo.write(0);
    delay(1000);
    Serial.println("Servo 90");
    myServo.write(90);
    delay(1000);
  }

  // LEDs
  if (true) {
    Serial.println("LEDS");
    for (int i = 0; i < pow(2, 3); i++) {
      Serial.println(i);
      digitalWrite(maintenanceLedPin, decode(i, 0) ? HIGH : LOW);
      digitalWrite(runningLedPin, decode(i, 1) ? HIGH : LOW);
      digitalWrite(signalLedPin, decode(i, 2) ? HIGH : LOW);
      delay(500);
    }
  }

  // Photoresitor
  if (true) {
    Serial.println("Photoresistor");
    for (int i = 0; i < 10; i++) {
      Serial.println(analogRead(photoresistorPin));
      delay(10);
    }
  }
}
```


## Hardware Challenges

### Distributing Power
All the components can be powered by the 5V provided by the Arduino except for the stepper motor, which needs 5V from a stronger power supply. To be able to wire all of my components through the breadboard, one live rail is connected to the power supply, and the other to the Arduino. Both of the ground rails are connected directly to the Arduino to provide a common ground. To ensure the power supply does not provide signal to the "Arduino rail", you need to remove the jumper from the appropriate side of the power supply. When connecting the power supply to the breadboard, be sure also to check that the positive and negative indicators correctly align with the rails they are plugged into. If they don't you need to connect the supply to the other side of the breadboard. (Technically, you would instead treat the ground rail as the live rail and vice-versa, but that seems like a relatively sure-fire way to create confusion.)

### Stepper Motor Pins
When creating my test program to drive the stepper motor, it initially didn't work. The stepper motor would make noise, and the red LEDs on the driver board would turn on and off, but it wouldn't rotate. I ran the simple example program in the Arduino IDE to test if the problem was in my code, and sure enough the motor worked when I ran the example program. I eventually found that when you initialise the stepper motor interface, the pins are not meant to be consecutively ordered.

**Correct code**

```cpp
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
```

**My incorrect code**

```cpp
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11); // Note that the middle two pins are wrong
```

### Servo Motor and Infrared Receiver Library Incompatibility
After attaching all of my core components, I attached the Infrared receiver that would allow me to use the remote control on the machine (see below). When I did however, the receiver would rapidly pulse red as if receiving signals and the servo motor would make noise without turning - as if it were receiving malformed control signals. After an extensive debugging session, I found I could - without touching any of the wiring - run simple example programs that used only one of the two components without any issues. However, any program that used both would cause the issues to occur.

With a corrected worded internet search, I found a [forum post](https://forum.arduino.cc/t/irreceiver-library-servo-strange-behaviour/536118) from someone with the same issue. I discovered that the servo motor and IR receiver libraries I was using have compatibility issues with one another. Though initially I tried looking for other libraries I could use, my ultimate solution was to [detach the servo motor whenever it is not in use](https://forum.arduino.cc/t/servo-twitch-with-irremote-library/129288/3).

Consequently, this is what the current version of the `Hardware::write` method looks like
```cpp
void Hardware::write(bool value) {
  writeMotor.attach(writeMotorPin);
  msg(value ? "TRUE" : "FALSE");

  if (value) {
    writeMotor.write(0);
    delay(1000);
    writeMotor.write(180);
    delay(1000);
  } else {
    writeMotor.write(180);
    delay(1000);
    writeMotor.write(0);
    delay(1000);
  }

  writeMotor.detach();
}
```


## Implementing Maintenance Mode
After all the components were fully working, I implemented what I call "maintenance mode". This is a feature of the final program which I used for the assembly, debugging, and calibration of the machine, as well as when something goes wrong while it is running. Using the Infrared receiver and remote control provided in the kit, I can send commands to the program telling it to do certain things. The final program lets you:

* Turn maintenance mode on and off
* Start or pause the turning machine
* Rotate the stepper motor (which drives the disc) clockwise or anti-clockwise
* Change how much the stepper motor would rotate by when given the above instruction
* Write true/false to the current bit
* Rotate the servo motor (the write motor) to a 90 degree angle (useful for positing bits onto the disc in the right place)
* Output to the serial monitor a reading from the photoresistor (useful for calibrating the light threshold)
* Output to the serial monitor if the read head is reading true or false.

As well as outputting to the serial monitor, I use three LEDs on the breadboard to help understand what state the machine is in.
* Blue LED - Turns on whenever maintenance mode is active.
* Green LED - Turns on whenever the turning machine is running.
* Yellow LED - Blips whenever an input is received from the IR receiver.
