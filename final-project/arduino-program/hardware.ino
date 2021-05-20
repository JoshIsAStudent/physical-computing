// Include the libraries we will need. These libraries handle some of the complex parts of controlling the eltronics for us, so we don't have to!
#include "hardware.h"

// Hardware
// This class controls all of the Arduino hardware and electronics. This includes that used by the A-Machine, as well as that used for maintenance mode.
class Hardware {
  public:

    // Program methods
    void setup() {
      Serial.begin(9600);

      pinMode(photoresistorPin, INPUT);

      pinMode(runningLedPin, OUTPUT);
      pinMode(maintenanceLedPin, OUTPUT);
      pinMode(signalLedPin, OUTPUT);

      writeMotor.attach(writeMotorPin);
      discMotor(discMotorStepsPerRevolution, discMotorPins[0], discMotorPins[1], discMotorPins[2], discMotorPins[3]);
    }

    void loop() {
      digitalWrite(runningPin, amachine->running ? HIGH : LOW, );
      digitalWrite(maintenancePin, maintenanceMode ? HIGH : LOW, );
    }

    // A Machine methods
    bool read() {
      return readLight > lightThreshold;
    }

    void write(bool value) {
      if (value) {
        writeMotor.write(0);
        writeMotor.write(180);
      } else {
        writeMotor.write(180);
        writeMotor.write(0);
      }
    }

    void move(int amt) {
      discMotor.step(amt * stepsPerBit);
    }

    void msg(String msg) { // This function is not really necessary for this program, but does ensure that the Hardward class is the only class directly interfacing with the serial port.
      Serial.println(msg);
    }

    // Photoresistor methods
    void calibrateLight() {
      msg("Please ensure the read head photoresitor is blocked");
      countdown();
      int low = readLight();

      msg("Please ensure the read head photoresitor is unblocked");
      countdown();
      int high = readLight();

      lightThreshold = (low + high) / 2;
      msg("New light threshold: " + lightThreshold)
    }

    int readLight() {
      float total = 0;
      for (int i = 0; i < 10; i++) {
        total += analogRead(photoresistorPin);
        delay(20);
      }
      return total / 10;
    }

    // Countdown method, used in other methods
    void countdown() {
      for (size_t i = 3; i > 1; i++) {
        Serial.print(String(i).concat(", "));
        delay(1000);
      }
      Serial.println("1.");
      delay(1000);
    }
};
