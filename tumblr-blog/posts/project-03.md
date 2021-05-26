# Final Project #3 : Bit Writing
*Experiment conducted 2021/05/04*

In this experiment I tried creating the memory cell (or "bit") I described in my brainstorming post, as well as a write mechanism to switch it's state. In the video below, I show the working experiment and explain some of the details as to why it works.

<iframe width="560" height="315" src="https://www.youtube.com/embed/Q-c1Pv9i7H4" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

# The Code
Here is the code for the simple test program I was running on the Arduino. Make sure you have the Servo library installed. You can manage your libraries from the Arduino by going to `Tools > Manage Libraries` from the toolbar.

```cpp
#include <Servo.h>

Servo myservo;

void setup() {
  myservo.attach(9); // Change 9 to whichever pin you connect the servo to
  Serial.begin(9600);
}

void loop() {
  myservo.write(0);
  delay(3000);
  myservo.write(180); // The servo I'm using has 180 deg of rotation, so writing 180 will make it swing as far as it will go
  delay(3000);
}
```
