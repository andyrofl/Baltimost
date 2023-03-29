#include <DRV8835.h>
#include <HBridgeMotor.h>
#include <InInMotor.h>
#include <InInPWMMotor.h>
#include <L298.h>
#include <Motor.h>
#include <MotorDriver.h>
#include <PhaseEnableMotor.h>
#include <SN754410.h>
#include <TB67H420FTG.h>

/*
 * Initialize our driver with the pins (motorA1, motorA2, motorB1, motorB2) and we're assuming:
 * Motor A = Left motor
 * Motor B = Right motor
 * The pins here would map to AIN1, AIN2, BIN1, BIN2 respectively
 */
DRV8835 driver(29, 25, 6, 8);


void setup() {
  // The only thing left to do is call init() so the library can initialize the pins
        driver.init();
        
  // Now, what we will do is just call our main code here so that it only happens once

  // Let's move the left motor forward a bit (our motor speed is valued from -100 to +100)
  //driver.setMotorAPower(50);  // Set the motor speed to 50% in a forward direction
  //delay(1000);                // Wait a second
  //driver.motorABrake();       // Stop our motor, we can brake or coast (self explanatory right)

  // Let's move the right motor forward a bit (Motor B this time)
  //driver.setMotorBPower(50);  // Set the motor speed to 50% in a forward direction
  //delay(1000);                // Wait a second
  //driver.motorBBrake();       // Stop our motor

  // Now let's control both motors to drive straight
  //driver.setMotorAPower(50);
  //driver.setMotorBPower(50);
  //delay(1000);                // Wait a second
  //driver.brakeAll();          // Notice here we can brake both motors using the brakeAll() function

  // That's it! Now you can see how to control each motor or both motors at the same time.
  // Feel free to change the word 'brake' with 'coast' wherever it shows up to see how coast might differ.
}

void loop() {
    // Now let's control both motors to drive straight
  driver.setMotorAPower(50);
  driver.setMotorBPower(50);
  delay(1000);                // Wait a second
  driver.brakeAll();          // Notice here we can brake both motors using the brakeAll() function
  delay(1000);                // Wait a second
}
