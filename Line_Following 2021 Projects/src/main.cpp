//the environment this code is written for, has already been pre-configured

#include <Arduino.h>
#include <Servo.h>
#include <NewPing.h>

#define IRSensorRight 12
#define IRSensorLeft 11

int motorSpeed = 140; //fixed but this is where we create a function
// motorSpeed(); its varied by several factors

int ENA = 2; //pwm enabled pin
int IN1 = 4;
int IN2 = 3;


int ENB = 5; //pwm enabled pin
int IN3 = 6;
int IN4 = 7;


int trigPin = 22; //trigger pin for USS
int echoPin = 24; //echo pin fro USS

Servo servo_motor; //create a servo object
long duration, cm, inches;


void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void turnRight()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //to motors 3/4
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void turnLeft()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //to motors 3/4
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void moveBack()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //to motors 3/4
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

void moveForward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  //to motors 3/4
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}



void setup() {
  // put your setup code here, to run once:

  //change the frequency of the PWM signal on pins D5/6
  TCCR0B = TCCR0B & B11111000 | B00000010;

  //for the motors 1 and 2
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  servo_motor.attach(8);
  servo_motor.write(90);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  //ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IRSensorRight, INPUT);
  pinMode(IRSensorLeft, INPUT);
  stopMotors();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin,HIGH);

  //convert the time to distance
  cm = (duration/2) / 29.1; //or multiply by 0.0343
  inches = (duration/2) / 74; //or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(2);

  if(cm>30)
  {
    int rightIRSensorValue = digitalRead(IRSensorRight);
    int leftIRSensorValue = digitalRead(IRSensorLeft);

    //if none of the sensors detects black line, then go straight
    if(rightIRSensorValue == LOW && leftIRSensorValue == LOW)
    {
      moveForward();
    }
    //if right sensors detect black-line, turn right
    else if(rightIRSensorValue == HIGH && leftIRSensorValue == LOW)
    {
      turnRight();
    }
    //if left sensor detect black-line, go left
    else if(rightIRSensorValue == LOW && leftIRSensorValue == HIGH)
    {
      turnLeft();
    }
    //if both sensors detect black_lines, move forward
    else if(rightIRSensorValue == HIGH && leftIRSensorValue == HIGH)
    {
      moveForward();
    }
  }

  else
  {
    stopMotors();
    servo_motor.write(40); 
    delay(3000);
    servo_motor.write(110);
    delay(3000);
    servo_motor.write(180); 
    delay(3000);
    servo_motor.write(110);

    turnLeft();
    delay(3000);
  }

}

