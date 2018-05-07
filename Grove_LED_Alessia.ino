/*
Author: Alessia Capancioni :)
Program: accensione di un led con effetto fading
*/

const int pinLed1 = 3;
const int pinLed2 = 5;
const int breath = 5;
const int delay1 = 10;
const int delay2 = 50;
const int maxIntensity = 255;

void setup()
{
 pinMode(pinLed1 , OUTPUT);
 pinMode(pinLed2 , OUTPUT);
}

void loop()
{
 for(int i=0 ; i<=maxIntensity ; i++)
 {
   analogWrite(pinLed1 , i);
   analogWrite(pinLed2 , maxIntensity-i);
   delay (breath);
 }
 delay (delay1);

 for(int i=maxIntensity ; i>=0 ; i--)
 {
   analogWrite(pinLed1 , i);
   analogWrite(pinLed2 , maxIntensity-i);
   delay (breath);
 }
 delay (delay2);
}