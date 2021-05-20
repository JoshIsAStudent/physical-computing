#include "hardware.h"

// Program methods
Hardware::Hardware() :
  discMotor(discMotorStepsPerRevolution, discMotorPins[0], discMotorPins[1], discMotorPins[2], discMotorPins[3])
{
  Serial.begin(9600);

  pinMode(photoresistorPin, INPUT);

  pinMode(runningLedPin, OUTPUT);
  pinMode(maintenanceLedPin, OUTPUT);
  pinMode(signalLedPin, OUTPUT);

  writeMotor.attach(writeMotorPin);
}

void Hardware::loop() {
  digitalWrite(runningLedPin, amachine->running ? HIGH : LOW );
  digitalWrite(maintenanceLedPin, maintenanceMode ? HIGH : LOW );
}

// A Machine methods
bool Hardware::read() {
  return readLight() > lightThreshold;
}

void Hardware::write(bool value) {
  if (value) {
    writeMotor.write(0);
    writeMotor.write(180);
  } else {
    writeMotor.write(180);
    writeMotor.write(0);
  }
}

void Hardware::move(int amt) {
  discMotor.step(amt * discMotorStepsPerBit);
}

void Hardware::msg(String msg) { // This function is not really necessary for this program, but does ensure that the Hardward class is the only class directly interfacing with the serial port.
  Serial.println(msg);
}

// Photoresistor methods
void Hardware::calibrateLight() {
  msg("Please ensure the read head photoresitor is blocked");
  countdown();
  int low = readLight();

  msg("Please ensure the read head photoresitor is unblocked");
  countdown();
  int high = readLight();

  lightThreshold = (low + high) / 2;
  msg("New light threshold: " + lightThreshold);
}

int Hardware::readLight() {
  float total = 0;
  for (int i = 0; i < 10; i++) {
    total += analogRead(photoresistorPin);
    delay(20);
  }
  return total / 10;
}

// Countdown method, used in other methods
void Hardware::countdown() {
  for (size_t i = 3; i > 1; i++) {
    Serial.print(String(i).concat(", "));
    delay(1000);
  }
  Serial.println("1.");
  delay(1000);
}
