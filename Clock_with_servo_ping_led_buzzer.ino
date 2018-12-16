#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
Servo servo_mot;

const int led = 4;
const int pushButton = 5;
const int buzzer = 6;
const int ping = 7;
int ore, min, sec;
long duration, cm;
int pos = 0;
int letturaButton;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pushButton, INPUT);
  servo_mot.attach(3);
  Serial.begin(9600);
  lcd.begin(16, 2);
  letturaButton = 0;
  lcd.clear();
  noTone(buzzer);
  servo_mot.write(0);
  
  digitalWrite(led, HIGH);
}

void if1()
{
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.print("*"); 
    
    digitalWrite(led, LOW);
    
    pinMode(ping, OUTPUT);
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(5);
    digitalWrite(ping, LOW);

    pinMode(ping, INPUT);
    duration = pulseIn(ping, HIGH);
    cm = duration/29/2;
    
    if(cm<150)
    {
     tone(buzzer, 440);
     Serial.print("cm ");
     Serial.println(cm);
    } 
    delay(30000);
}

void if2()
{
    pinMode(ping, OUTPUT);
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(5);
    digitalWrite(ping, LOW);

    pinMode(ping, INPUT);
    duration = pulseIn(ping, HIGH);
    cm = duration/29/2;
    
    pos = map(cm, 15, 180, 0, 180);
    servo_mot.write(pos);
    
    Serial.print("Gradi ");
    Serial.println(pos);
    
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.print("+");
    
    delay(60000);
    servo_mot.write(0);
}

void if3()
{
  lcd.clear();
  lcd.setCursor(15, 0);
  lcd.print("-");
  
  servo_mot.write(120);
  
    pinMode(ping, OUTPUT);
    digitalWrite(ping, LOW);
    delayMicroseconds(2);
    digitalWrite(ping, HIGH);
    delayMicroseconds(5);
    digitalWrite(ping, LOW);

    pinMode(ping, INPUT);
    duration = pulseIn(ping, HIGH);
    cm = duration/29/2;
  
  lcd.setCursor(0, 0);
  lcd.print("cm ");
  lcd.print(cm);
  
  delay(10000);
  servo_mot.write(0);
}

void loop()
{ 
  for(ore=0;ore<12;ore++)
  {
    for(min=0;min<60;min++)
    {
      for(sec=0;sec<60;sec++)
      {
        lcd.clear();
        lcd.setCursor(3,1);
        lcd.print("ORA ");
        lcd.print(ore);
        lcd.print(":");
        lcd.print(min);
        lcd.print(":");
        lcd.print(sec);
        
        
        letturaButton = digitalRead(pushButton);
        if(letturaButton == HIGH && !(ore==0 && min==0 && sec==50))
        {
          if1();
          setup();

            if(ore==0 && min==0 && sec==50)
          {
            if3();
          }
        }
        

        if(ore==0 && min==0 && sec==10)
        {
          if2();
        }
        
        
        
        delay(996);
      }
    }
  }
  lcd.clear(); 
}
