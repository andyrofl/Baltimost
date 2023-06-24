/** 
 * Author: Lydia Mejias-Dansbach and Andy Pacher
 * Date created: Feb 8, 2023
 * Date last modified: May 12, 2023
 */


// Library included in Arduino IDE
#include <AccelStepper.h>


// Pin assignments for Teensy 4.1
const int pitchStepperStepPin = 25;
const int pitchStepperDirPin = 24;
const int yawStepperStepPin = 12;
const int yawStepperDirPin = 11;
const int feedStepperStepPin = 29;
const int feedStepperDirPin = 28;
const int M1DIR = 2;
const int M1PWM = 3;
const int M2DIR = 4;
const int M2PWM = 5;
const int IR_sense = 23;
const int pitchLimitSwitchPin = 19;
const int yawLimitSwitchPin = 18;

// Set constants for steps, yaw and pitch degrees, stepper and flywheel speed and stepper acceleration
const int stepsPerRevolution = 200;
const float pitchDegreePerStep = 180.0 / stepsPerRevolution;
const float yawDegreePerStep = 360.0 / stepsPerRevolution;
const int stepperSpeed = 100;
const int stepperAcceleration = 100;
int flywheelSpeed = 215;


// Include stepper drivers step and direction pins
AccelStepper pitchStepper(AccelStepper::DRIVER, pitchStepperStepPin, pitchStepperDirPin);
AccelStepper yawStepper(AccelStepper::DRIVER, yawStepperStepPin, yawStepperDirPin);
AccelStepper feedStepper(AccelStepper::DRIVER, feedStepperStepPin, feedStepperDirPin);


/**
 * Setup function. Runs once at program startup
 */
void setup() {
  Serial.begin(9600);
  Serial.println("RESET");
  pitchStepper.setMaxSpeed(stepperSpeed);
  pitchStepper.setAcceleration(stepperAcceleration);
  yawStepper.setMaxSpeed(stepperSpeed);
  yawStepper.setAcceleration(stepperAcceleration);
  feedStepper.setMaxSpeed(50);
  feedStepper.setAcceleration(200);
Serial.println("set vars");

  pinMode(pitchLimitSwitchPin, INPUT_PULLUP);
  pinMode(yawLimitSwitchPin, INPUT_PULLUP);
  pinMode(IR_sense, INPUT_PULLUP);
  pinMode(M1DIR, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(M2PWM, OUTPUT);
  Serial.println("set pins");


  


  homePitch();
  homeYaw();
Serial.println("homed");

  // Full yaw and pitch
  setPitchAndYaw(15, 0);
}


/**
 * Main program loop. 
 */
void loop() {
  // Yaw turn clockwise, pitch adjust each angle shot, then run shootBall to shoot balls into containers
  
  //Left-most ship target 1
  setPitchAndYaw(26, -5); // Pitch: 26 degrees, Yaw: -5 degrees
  flywheelSpeed = 200; //0-255 range of power for DC motors
  shootBall(); //call helper function to shoot ball

//ship target 2
  setPitchAndYaw(24, 170);
  flywheelSpeed = 215;
  shootBall();
//ship target 3
  setPitchAndYaw(22, 435);
  flywheelSpeed = 200;
  shootBall();
//ship target 4
  setPitchAndYaw(24, 700);
  flywheelSpeed = 215;
  shootBall();
//ship target 5
  setPitchAndYaw(26, 870);
  flywheelSpeed = 220;
  shootBall();


//Yaw turn counterclockwise, lower the angle of barrel, adjust speed of flywheels to shoot down remaining ships
//Right-most rowboat target 1
  setPitchAndYaw(15, 850);
  flywheelSpeed = 200;
  shootBall();
//Rowboat target 2
  setPitchAndYaw(15, 610);
  flywheelSpeed = 215;
  shootBall();
//Rowboat target 3
  setPitchAndYaw(15, 200);
  flywheelSpeed = 200;
  shootBall();
//Rowboat target 4
   setPitchAndYaw(15, -5);
  flywheelSpeed = 220;
  shootBall();


  //pause program indefinitely
  while (true) {
    delay(1000);
  }
}
/**
 * function to set zero point for the pitch stepper motor
 */
void homePitch() {
pitchStepper.setMaxSpeed(stepperSpeed); // Fast jog forward for barrel


// Adjust pitch axis until the limit switch is triggered
  while (digitalRead(pitchLimitSwitchPin)) {
    pitchStepper.move(-5);
    pitchStepper.run();
  }
  pitchStepper.setCurrentPosition(0); //Set zero point for pitch stepper
// Back off from the limit switch
  pitchStepper.move(5);
  while (pitchStepper.run()){} //wait until pitchStepper is no longer running
  // Zero pitch
  pitchStepper.setCurrentPosition(0);
}
/**
 * this function sets the zero point for the yaw stepper motor
 */
void homeYaw() {
// Fast jog counterclockwise around base gear
  yawStepper.setMaxSpeed(stepperSpeed);


// Move yaw axis until the limit switch is triggered
  while (digitalRead(yawLimitSwitchPin)) {
    yawStepper.move(-15);
    yawStepper.run();
  }


// Back off from the limit switch
  yawStepper.move(100);
  while (yawStepper.distanceToGo() != 0) {
    yawStepper.run();
  }


// Set zero point for yaw stepper
  yawStepper.setCurrentPosition(0);
  
// Reset yaw stepper speed to its original value
  yawStepper.setMaxSpeed(stepperSpeed);
}
/**
 * function sets pitch and yaw steppers to specified angles
 */
void setPitchAndYaw(float pitchAngle, float yawAngle) {
  int pitchStepsToMove = pitchAngle / pitchDegreePerStep;
  int yawStepsToMove = yawAngle / yawDegreePerStep;


  pitchStepper.moveTo(pitchStepsToMove);
  yawStepper.moveTo(yawStepsToMove);


  while (pitchStepper.distanceToGo() != 0 || yawStepper.distanceToGo() != 0) {
    pitchStepper.run();
    yawStepper.run();
  }
}




/**
 * This function runs the DC motors to spin the flywheels to shoot the Nerf balls
 * the feedStepper motor is also run while the DC motors are running
 */
void shootBall() {//change function args to take number of balls to shoot
  //set dir and PWM pins to programmed values to turn on DC motor driver output
  digitalWrite(M1DIR, HIGH);
  analogWrite(M1PWM, flywheelSpeed);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M2PWM, flywheelSpeed);

  /*
   * here we should enter a loop that checks if the IR sensor has been interrupted --IR_sense
   *  if yes, increment counter
   *    immediately check if this makes the count equal the argument
   *    if yes, exit the loop
   *    if no, wait briefly to prevent double count and then continue the loop --will likely require trial and error to find proper wait time
   *  if no, do not increment counter. allow loop to continue
   */
  delay(100);
  //move feedStepper counterclockwise to feed balls while firing
  feedStepper.move(-200);
  while (feedStepper.distanceToGo() != 0) {
    feedStepper.run();//wait until feedStepper has finished movement
  }
  delay(100);
  //end deprecated section

  //reset PWM and dir output pins to turn off DC motor driver output
  digitalWrite(M1DIR, LOW);
  analogWrite(M1PWM, 0);
  digitalWrite(M2DIR, LOW);
  analogWrite(M2PWM, 0);
}
