#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

//LEDs and Buttons and buzzers
int led1;
int b1, b2, b3, b4, b5, b6, b7, b8;
int buzzer;

//globals
long future;
double ans;
int displayNum;
int currNum;
int operation;

//boolean b1Pressed,b2Pressed,b3Pressed,b4Pressed,b5Pressed,b6Pressed,b7Pressed,b8Pressed;
void setup()
{
  Serial.begin(9600);

  //LEDs
  led1 = 8;

  pinMode(led1, OUTPUT);

  //BUTTONS
  b1 = A0;
  b2 = A1;
  b3 = A2;
  b4 = A3; 
  b5 = A4;
  b6 = A5;
  b7 = 6;
  b8 = 7;

  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  pinMode(b4, INPUT);
  pinMode(b5, INPUT);
  pinMode(b6, INPUT);
  pinMode(b7, INPUT);
  pinMode(b8, INPUT);

  //BUZZER
  buzzer = 9;

  pinMode(buzzer,OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  //instantiate globals
  future = 0;
  //b1Pressed,b2Pressed,b3Pressed,b4Pressed,b5Pressed,b6Pressed,b7Pressed,b8Pressed = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  playTone();
}
void playTone(){
  int b1state = digitalRead(b1);
  int b2state = digitalRead(b2);
  int b3state = digitalRead(b3);
  int b4state = digitalRead(b4);
  int b5state = digitalRead(b5);
  int b6state = digitalRead(b6);
  int b7state = digitalRead(b7);
  int b8state = digitalRead(b8);

  long time = millis();
  //int secs = time/1000;

  if(b1state == 1 && time >= future){
    
    future = time + 250;
  }
  else{
    noTone(buzzer);
  }

}
