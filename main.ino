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
int firstNum;
int secondNum;
int posCursor;

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
  ans = 0;
  displayNum = 5;
  currNum = 0;
  operation = 0;
  firstNum = 0;
  secondNum = 0;
  posCursor = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  //checkButtons();
  onClick();
}
void onClick(){
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
  
  lcd.setCursor(posCursor,0);
  blinkNum(displayNum);
  
  if(b1state == 1 && time >= future){
    if(displayNum != 0){
      displayNum--;
    }
    future = time + 250;
    
    lcd.setCursor(posCursor, 0);
    lcd.print(displayNum);
  }
  else if(b2state == 1 && time >= future){
    future = time + 250;
    
    lcd.setCursor(posCursor,0);
    lcd.print(displayNum);
    
    currNum = currNum * 10 + displayNum;
    displayNum = 5;
    posCursor++;
    
  }
  else if(b3state == 1 && time >= future){
    if(displayNum != 9){
      displayNum++;
    }
    future = time + 250;
    
    lcd.setCursor(posCursor, 0);
    lcd.print(displayNum);
  }
  else if(b4state == 1 && time >= future){
    firstNum = currNum;
    currNum = 0;
    operation = 1;
    future = time + 250;
  }
  else if(b5state == 1 && time >= future){
    firstNum = currNum;
    currNum = 0;
    operation = 2;
    future = time + 250;
  }
  else if(b6state == 1 && time >= future){
    firstNum = currNum;
    currNum = 0;
    operation = 3;
    future = time + 250;
  }
  else if(b7state == 1 && time >= future){
    firstNum = currNum;
    currNum = 0;
    operation = 4;
    future = time + 250;
  }
  else if(b8state == 1 && time >= future){
    secondNum = currNum;
    currNum = 0;
    operation = 0;
    future = time + 250;
  }
  else{
    noTone(buzzer);
  }
}

//Blinking the current number on the LCD
void blinkNum(int num) {
  long time = millis();
  long sec = time/500;
  
  if(sec%2 == 0)
    lcd.print(num);
  else
    lcd.print(" ");
}

//Checking the Button state
void checkButtons(){
  int b1state = digitalRead(b1);
  int b2state = digitalRead(b2);
  int b3state = digitalRead(b3);
  int b4state = digitalRead(b4);
  int b5state = digitalRead(b5);
  int b6state = digitalRead(b6);
  int b7state = digitalRead(b7);
  int b8state = digitalRead(b8);

  Serial.print("b1 = ");
  Serial.println(b1state);
  Serial.print("b2 = ");
  Serial.println(b2state);
  Serial.print("b3 = ");
  Serial.println(b3state);
  Serial.print("b4 = ");
  Serial.println(b4state);
  Serial.print("b5 = ");
  Serial.println(b5state);
  Serial.print("b6 = ");
  Serial.println(b6state);
  Serial.print("b7 = ");
  Serial.println(b7state);
  Serial.print("b8 = ");
  Serial.println(b8state);
}
