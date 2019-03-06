#include <Arduino.h>
#include <CheapStepper.h>
#include <Encoder.h>

long oldPosition = -999;
long newPosition = -999;

Encoder myEncoder(2,3);
CheapStepper myStepper (8,9,10,11);  

void setup() {
  // put your setup code here, to run once:

  myStepper.setRpm(10);
  Serial.begin(115200);

}

void loop() {
  //put your main code here, to run repeatedly:

  myStepper.run();
  newPosition = myEncoder.read();
  if (newPosition != oldPosition) {
    myStepper.newMoveDegrees(newPosition < oldPosition, abs(newPosition-oldPosition));
    oldPosition = newPosition;
  }

  if (Serial.available()) {
    Serial.read();
    Serial.println("Serial reset to 0");
    myStepper.newMoveToDegree(newPosition == oldPosition, 0);
    myEncoder.write(0);
  }

}