#include <AccelStepper.h>

// Pin assignments
const int pitchStepperStepPin = 2;
const int pitchStepperDirPin = 3;
const int yawStepperStepPin = 4;
const int yawStepperDirPin = 5;
const int feedStepperStepPin = 12;
const int feedStepperDirPin = 14;
const int pitchLimitSwitchPin = 10;
const int yawLimitSwitchPin = 11;
const int M1DIR = 6;
const int M1PWM = 7;
const int M2DIR = 8;
const int M2PWM = 9;

const int stepsPerRevolution = 200;
const float pitchDegreePerStep = 180.0 / stepsPerRevolution;
const float yawDegreePerStep = 360.0 / stepsPerRevolution;
const int stepperSpeed = 100;
const int stepperAcceleration = 10;
const int flywheelSpeed = 255;

AccelStepper pitchStepper(AccelStepper::DRIVER, pitchStepperStepPin, pitchStepperDirPin);
AccelStepper yawStepper(AccelStepper::DRIVER, yawStepperStepPin, yawStepperDirPin);
AccelStepper feedStepper(AccelStepper::DRIVER, feedStepperStepPin, feedStepperDirPin);

void setup() {
  pitchStepper.setMaxSpeed(stepperSpeed);
  pitchStepper.setAcceleration(stepperAcceleration);
  yawStepper.setMaxSpeed(stepperSpeed);
  yawStepper.setAcceleration(stepperAcceleration);
  feedStepper.setMaxSpeed(50);
  feedStepper.setAcceleration(5);

  pinMode(pitchLimitSwitchPin, INPUT_PULLUP);
  pinMode(yawLimitSwitchPin, INPUT_PULLUP);
  pinMode(M1DIR, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  pinMode(M2DIR, OUTPUT);
  pinMode(M2PWM, OUTPUT);

  Serial.begin(9600);
  // while (!Serial);
  // Serial.println("Start");  


  homePitch();
  homeYaw();
  // Full yaw and pitch
  setPitchAndYaw(90, 180);

  // Center
  setPitchAndYaw(30, 90);
  Serial.println("Homing routines completed.");
}

void loop() {
  // setPitchAndYaw(45, 90);
  // Serial.print("Pitch: 45 degrees, Yaw: 90 degrees\n");
  // shootBall();

  // setPitchAndYaw(45, 150);
  // Serial.print("Pitch: 45 degrees, Yaw: 150 degrees\n");
  // shootBall();

  // setPitchAndYaw(45, 200);
  // Serial.print("Pitch: 45 degrees, Yaw: 200 degrees\n");
  // shootBall();

  // setPitchAndYaw(45, 250);
  // Serial.print("Pitch: 45 degrees, Yaw: 250 degrees\n");  
  shootBall();

  Serial.println("Waiting forever");
  while(true){
    delay(1000);
  }
}
void homePitch() {
  // Fast jog
  pitchStepper.setMaxSpeed(stepperSpeed);
  Serial.println("Start pitch");

  // Move pitch axis until the limit switch is triggered
  while (digitalRead(pitchLimitSwitchPin)) {
    pitchStepper.move(-15);
    pitchStepper.run();
  }
Serial.println("Pitch LS triggered");
  
  // Back off from the limit switch
  pitchStepper.move(5);
  while (pitchStepper.distanceToGo() != 0) {
    pitchStepper.run();

  }
  pitchStepper.setCurrentPosition(0);
Serial.println("Pitch position zeroed");

  // Reset stepper speed to its original value
  pitchStepper.setMaxSpeed(stepperSpeed);
}

void homeYaw() {
  // Fast jog
  yawStepper.setMaxSpeed(stepperSpeed);
Serial.println("Start Yaw");

  // Move yaw axis until the limit switch is triggered
  while (digitalRead(yawLimitSwitchPin)) {
    yawStepper.move(-15);
    yawStepper.run();
  }
Serial.println("Yaw LS trigged");

  // Back off from the limit switch
  yawStepper.move(100);
  while (yawStepper.distanceToGo() != 0) {
    yawStepper.run();
  }
  yawStepper.setCurrentPosition(0);
Serial.println("Yaw position zeroed");

  // Reset stepper speed to its original value
  yawStepper.setMaxSpeed(stepperSpeed);
}

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

// Home functions for pitch and yaw remain the same

void shootBall() {

  Serial.println("Spin fly wheels...");
  digitalWrite(M1DIR, HIGH);
  analogWrite(M1PWM, flywheelSpeed);
  digitalWrite(M2DIR, HIGH);
  analogWrite(M2PWM, flywheelSpeed);

  delay(100);

  Serial.println("Turning feeder...");
  feedStepper.move(100);
  while (feedStepper.distanceToGo() != 0) {
    feedStepper.run();
  }

  delay(100);

  Serial.println("Stop flywheels...");
  digitalWrite(M1DIR, LOW);
  analogWrite(M1PWM, 0);
  digitalWrite(M2DIR, LOW);
  analogWrite(M2PWM,0);

  Serial.println("Ball shot.");
}
