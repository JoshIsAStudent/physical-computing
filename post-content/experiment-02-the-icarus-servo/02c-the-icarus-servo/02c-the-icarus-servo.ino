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
