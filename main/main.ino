const int one =1;
const int pin1 =A0;
const int indicatorLedPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(indicatorLedPin, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("serial initialized");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(true){
    if (Serial.available() > 0) {
      int thisChar = Serial.read();
      Serial.print("You sent me: \'");
      Serial.write(thisChar);
    }
    digitalWrite(indicatorLedPin, LOW);
    wait(1000);
    digitalWrite(indicatorLedPin, HIGH);
    wait(1000);
  }
  }
}
