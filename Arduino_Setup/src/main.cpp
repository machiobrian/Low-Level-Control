#include <Arduino.h>
#define onBoardPin 13

void setup() {
  // put your setup code here, to run once:
  pinMode(onBoardPin, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(onBoardPin, HIGH);
  delay(1250);
  digitalWrite(onBoardPin, LOW);
  delay(1000);

  Serial.print("Blink || Stop \n");
}