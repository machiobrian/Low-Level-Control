#include <Arduino.h>

//initialize LED pin
int led_pin = 13;

void setup()
{
    //declare the pin as output
    pinMode(led_pin, OUTPUT);
}
void loop()
{
    //fade the LED
    for(int i=0; 1<255; i++)
    {
        analogWrite(led_pin, i);
        delay(5);
    }
    for(int i=255; i>0; i--)
    {
        analogWrite(led_pin,i);
        delay(5);
    }
}