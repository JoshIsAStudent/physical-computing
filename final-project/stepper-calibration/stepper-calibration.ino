#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
void setup() {
  myStepper.setSpeed(16);
  pinMode(7, INPUT);
  delay(1000);
}

void wait() {
  delay(1000);
  while (digitalRead(7) == LOW) delay(50);
}

void loop() {
  wait();
  myStepper.step(stepsPerRevolution);
  wait();
  myStepper.step(-stepsPerRevolution);
}
