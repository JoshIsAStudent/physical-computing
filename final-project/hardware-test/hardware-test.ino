#include <Stepper.h>
#include <Servo.h>

// Stepper motor
const int stepperStepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int stepperRPM = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
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
  if (false) {
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
