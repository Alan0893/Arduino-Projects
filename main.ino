//LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

//LEDs and Buttons and buzzers
int led1;
int b1, b2, b3, b4, b5, b6, b7, b8;
int buzzer;

//Globals
long future;
double ans;
int displayNum;
int currNum;
int operation;
int firstNum;
int secondNum;
int posCursor;
boolean gotAns;
int prevCursor;
int opPos;

//SETUP 
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
  b7 = 7;
  b8 = 6;
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

  //Setting up the LCD number of columns and rows
  lcd.begin(16, 2);

  //Instantiating Global Variables
  future = 0;     //For Button Pressing
  ans = 0;        //Final Answer
  displayNum = 5; //The current single number being displayed
  currNum = 0;    //The current whole number being displayed
  operation = 0;  //The operation being called (+, -, x, /)
  firstNum = 0;   //The first number 
  secondNum = 0;  //The second number after the operation
  posCursor = 0;  //The position of the cursor on the LCD
  gotAns = false; //Checks if answer was obtained
  prevCursor = 0; //Previous cursor on the LCD
  opPos = 0;   //Position of the operation
}

void loop() {
  //checkButtons();
  onClick();
  Serial.print("posCursor = ");
  Serial.println(posCursor);
  Serial.print("opPos = ");
  Serial.println(opPos);
}
void onClick(){
  //The states of the buttons
  int b1state = digitalRead(b1);
  int b2state = digitalRead(b2);
  int b3state = digitalRead(b3);
  int b4state = digitalRead(b4);
  int b5state = digitalRead(b5);
  int b6state = digitalRead(b6);
  int b7state = digitalRead(b7);
  int b8state = digitalRead(b8);

  //Time for future (button pressing)
  long time = millis();
  //int secs = time/1000;
  
  //Setting the cursor of the LCD
  if(!gotAns) { //While theres no answer
    lcd.setCursor(posCursor,0); //Sets the cursor on the LCD  
    blinkNum(displayNum); //Blinks the current displayed number
  }
  else if(gotAns) { //Else answer was obtained
    lcd.setCursor(prevCursor,0);
    lcd.print(" "); //Print nothing after equal sign was pressed
  }
  
  if(b1state == 1 && time >= future){ //BUTTON 1 (<--)
    if(displayNum != 0){  //While the current displayed number isn't 0
      displayNum--;       //Subtract 1 : 5 --> 4 --> 3 ...
    }
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
    
    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);      //Displaying the number on the LCD 
  }
  else if(b2state == 1 && time >= future){  //BUTTON 2 (SELECT)
    future = time + 250;  //Prevents user from pressing button for 1/4 sec

    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);    //Displaying the number on the LCD

    currNum = currNum * 10 + displayNum;  //Getting the current number
    //firstNum = currNum;
    displayNum = 5; //Resetting the displayed number to 5 for next number
    posCursor++;  //Adding a column to the cursor position
  }
  else if(b3state == 1 && time >= future){ //BUTTON 3 (-->)
    if(displayNum != 9){  //While the current displayed number isn't 9
      displayNum++;       //Add 1 5 --> 6 --> 7 ...
    }
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
    
    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);      //Displaying the number on the LCD
  }
  else if(b4state == 1 && time >= future){  //BUTTON 4 (+)
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;  //going back 1 position to override the previous operation shown on LCD
    }
    else {
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans");
      posCursor = 3;
    }

    if(posCursor-opPos > 1)
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans+");
      operation = 1;
      posCursor = 4;
    }
    else {
      opPos = posCursor;
      lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
      lcd.print("+");   //Printing the plus sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 1;  //Setting operation to 1 for addition 
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b5state == 1 && time >= future){  //BUTTON 5 (-)
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;
    }
    else {
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans");
      posCursor = 3;
    }

    if(posCursor-opPos > 1)
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans+");
      operation = 1;
      posCursor = 4;
    }
    else {
      opPos = posCursor;
      lcd.setCursor(posCursor,0); //Setting the cursor on the LCD
      lcd.print("-"); //Printing the minus sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 2;  //Setting operation to 2 for subtraction
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b6state == 1 && time >= future){  //BUTTON 6 (x)
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;
    }
    else {
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans");
      posCursor = 3;
    }

    if(posCursor-opPos > 1)
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans+");
      operation = 1;
      posCursor = 4;
    }
    else {
      opPos = posCursor;
      lcd.setCursor(posCursor,0); //Setting the cursor on the LCD
      lcd.print("x"); //Printing the times sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 3;  //Setting operation to 3 for multiplication
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b7state == 1 && time >= future){  //BUTTON 7 (/)
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;
    }
    else {
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans");
      posCursor = 3;
    }

    if(posCursor-opPos > 1)
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();
      gotAns = false;
      firstNum = ans;
      lcd.setCursor(0, 0);
      lcd.print("Ans+");
      operation = 1;
      posCursor = 4;
    }
    else {
      opPos = posCursor;
      lcd.setCursor(posCursor,0); //Setting the cursor on the LCD
      lcd.print("/"); //Printing the divide sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 4;  //Setting operation to 4 for division
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b8state == 1 && time >= future){  //BUTTON 8 (=)
    secondNum = currNum;  //Makes the second number equal to currNum
    currNum = 0;  //Resetting currNum to 0 since second number was obtained

    if(operation == 0){ //If there was no answer
      ans = firstNum;   //Then the answer is the first number entered
    }
    else if(operation == 1){      //If the operation was 1 (+)
      ans = firstNum + secondNum; //Ans = first number plus second number
    }
    else if(operation == 2){      //If the operation was 2 (-)
      ans = firstNum - secondNum; //Ans = first number minus second number
    }
    else if(operation == 3){      //If operation was 3 (x)
      ans = firstNum * secondNum; //Ans = first number times second number
    }
    else if(operation == 4){      //If operation was 4 (/)
      ans = firstNum / secondNum; //Ans = first number divided by second number
    }

    lcd.setCursor(0,1); //Sets the cursor to print the answer on the LCD
    lcd.print((int)ans); //Prints the answer on the LCD
    gotAns = true;  //Sets gotAns to true, since answer was obtained

    prevCursor = posCursor;
    posCursor = 0;  //Resets posCursor to 0, since answer was obtained
    operation = 0;  //Operation is reset to 0, for new equation
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else{ //No button was pressed
    noTone(buzzer); //No sound
  }
}

//If a second operation is pressed after a second number is created
void onSecOp() {
  secondNum = currNum;  //Makes the second number equal to currNum
  currNum = 0;  //Resetting currNum to 0 since second number was obtained

  if(operation == 0){ //If there was no answer
    ans = firstNum;   //Then the answer is the first number entered
  }
  else if(operation == 1){      //If the operation was 1 (+)
    ans = firstNum + secondNum; //Ans = first number plus second number
  }
  else if(operation == 2){      //If the operation was 2 (-)
    ans = firstNum - secondNum; //Ans = first number minus second number
  }
  else if(operation == 3){      //If operation was 3 (x)
    ans = firstNum * secondNum; //Ans = first number times second number
  }
  else if(operation == 4){      //If operation was 4 (/)
    ans = firstNum / secondNum; //Ans = first number divided by second number
  }

  lcd.setCursor(0,1); //Sets the cursor to print the answer on the LCD
  lcd.print((int)ans); //Prints the answer on the LCD
  gotAns = true;  //Sets gotAns to true, since answer was obtained

  prevCursor = posCursor;
  posCursor = 0;  //Resets posCursor to 0, since answer was obtained
  operation = 0;  //Operation is reset to 0, for new equation
}

//Blinking the current number on the LCD
/**
 * @brief Will  blink the current displayed @param num every 1/2 sec
 * @param num 
 */
void blinkNum(int num) {
  long time = millis();
  long sec = time/500;
  
  if(sec%2 == 0)
    lcd.print(num);
  else
    lcd.print(" ");
}

//Blinks the LEDs
/**
 * @brief Will blink the @param led every 1/2 sec
 * @param led 
 */
void blinkLED(int led) {
  long time = millis();
  long sec = time/500;

  if(sec%2 == 0)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}

//Plays a tone on the buzzer every 1/2 second
/**
 * @brief Will play a @param tone on @param buzzer
 * @param buzzer 
 * @param tone 
 */
void playTone(int buz, double freq) {
  long time = millis();
  long sec = time/500;

  if(sec%2 == 0)
    tone(buz, freq);
  else
    noTone(buz);
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
