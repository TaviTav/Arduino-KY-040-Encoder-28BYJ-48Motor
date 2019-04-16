#include <Arduino.h>
#include <CheapStepper.h>
#include <Encoder.h>

uint8_t encoder_SW = 4;
long oldPosition = -999;
long newPosition = -999;

Encoder myEncoder(5,6);
CheapStepper myStepper (8,9,10,11);  

void setup() {
  // put your setup code here, to run once:

  myStepper.setRpm(10);
  Serial.begin(115200);
  pinMode(encoder_SW, INPUT);
}

void loop() {
  //put your main code here, to run repeatedly:

  myStepper.run();
  newPosition = myEncoder.read();
  if (newPosition != oldPosition) {
    myStepper.newMoveDegrees(newPosition < oldPosition, abs(newPosition-oldPosition));
    Serial.print("Degrees asked: ");
    Serial.println(abs(newPosition-oldPosition));
    Serial.print("Steps to do 1 rot=2048*2: ");
    Serial.println(myStepper.getStepsLeft());
    oldPosition = newPosition;
  }

  if (Serial.available()) {
    Serial.read();
    Serial.println("Serial reset to 0");
    myStepper.newMoveToDegree(newPosition == oldPosition, 0);
    myEncoder.write(0);
  }

  if (digitalRead(encoder_SW) == LOW) { // Troubleshooting check if this needs to be == HIGH
    Serial.println("Button Reset to 0");
    myEncoder.write(0);
  }
}