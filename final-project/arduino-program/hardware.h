// Hardware
// This class controls all of the Arduino hardware and electronics. This includes that used by the A-Machine, as well as that used for maintenance mode.

#ifndef HARDWARE_H
#define HARDWARE_H

#include <Servo.h>
#include <Stepper.h>
#include "IRremote.h"
class AMachine; // Forward declaration of Hardware class so that we can create a pointer to it. If we included it instead, `machine.h` and `hardware.h` would have cyclic include dependicies

class Hardware {
  public:
    // Settings - Input pins
    const uint8_t photoresistorPin = A5;

    // Settings - Output pins
    const uint8_t maintenanceLedPin = 4;
    const uint8_t runningLedPin = 3;
    const uint8_t signalLedPin = 2;
    const uint8_t writeMotorPin = 6;
    const uint8_t irReceiverPin = 8;
    const uint8_t discMotorPins[4] = {10, 12, 11, 13};

    // Settings - Motors
    const float discMotorRPM = 17;
    const int discMotorStepsPerRevolution = 2048;
    const int discMotorStepsPerBit = 4;

    // Interfaces
    Stepper discMotor;
    Servo writeMotor;
    IRrecv irReceiver;
    AMachine* amachine;

    // Maintenance mode
    bool maintenanceMode = true;
    const int mmDiscStepAmt[6] = {20, 50, 100, 1000, discMotorStepsPerRevolution / 4, discMotorStepsPerRevolution};
    const int mmDiscStepAmtCount = 6;
    int mmDiscStepAmtInx = mmDiscStepAmtCount - 1;

    // Variables
    int lightThreshold = (730+1010) / 2;
    int readHeadOffset = -230;

    // Program methods
    Hardware();
    void setup();
    void loop();

    // A Machine methods
    bool read();
    void write(bool value);
    void move(int amt);
    void msg(String msg);

    // Photoresistor methods
    void calibrateLight();
    int readLight() ;

    // Infrared Remote methods
    void handleRemote();

    // Countdown method, used in other methods
    void countdown();
};

#endif
