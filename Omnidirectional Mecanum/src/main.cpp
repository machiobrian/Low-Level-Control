#include <Arduino.h>

int motorSpeed = 1; //HIGH to digital pins

//pin setup - forward wheels //right and wrong/left
int IN1 =2;
int IN2 =3;
int ENA =4; //pwm

int IN3 =5;
int IN4 =6;
int ENB =7; //pwm

void setup()
{
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
}

void forwardMotion()
{
  //move forward M1
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(ENA, motorSpeed);

  //move forward M2
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  digitalWrite(ENB, motorSpeed);

}

void reverseMotion()
{
    //move reverse M1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, motorSpeed);

  //move reverse M2
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(ENB, motorSpeed);
}

void loop()
{
  forwardMotion();
  //reverseMotion();
  
}