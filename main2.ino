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
boolean bPressed;

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
  bPressed = false;
}

void loop() {
  //checkButtons();
  //Getting and playing the frequency according to button pressed
  int note = getTone(displayNum);
  if(note == 0)
    noTone(buzzer);
  else
    tone(buzzer, note);

  onClick();
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
  
  //Setting the cursor of the LCD
  if(!gotAns) { //While theres no answer
    lcd.setCursor(posCursor,0); //Sets the cursor on the LCD  
    blinkNum(displayNum); //Blinks the current displayed number
  }
  else if(gotAns) { //Else answer was obtained
    lcd.setCursor(prevCursor,0);
    lcd.print(" "); //Print nothing after equal sign was pressed
  }
  
  if(b1state == 1 && time >= future && !bPressed){ //BUTTON 1 (<--)
    bPressed = true;  //Button was pressed  
    if(gotAns) {    //If there was an answer
        onReset();  //Reset all variables to default value
        lcd.clear();//Clears the LCD screen
    }

    if(displayNum != 0){  //While the current displayed number isn't 0
      displayNum--;       //Subtract 1 : 5 --> 4 --> 3 ...
    }

    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);      //Displaying the number on the LCD 
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
}
  else if(b2state == 1 && time >= future && !bPressed){  //BUTTON 2 (SELECT)
    bPressed = true;  //Button was pressed

    if(gotAns) {    //If there was an answer  
        onReset();  //Reset all variables to default value
        lcd.clear();//Clears the LCD screen
    }

    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);    //Displaying the number on the LCD

    currNum = currNum * 10 + displayNum;  //Getting the current number
    if(operation == 0)    //No operation
    	firstNum = currNum; //Make first number equal to the current number

    displayNum = 5; //Resetting the displayed number to 5 for next number
    posCursor++;  //Adding a column to the cursor position
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b3state == 1 && time >= future && !bPressed){ //BUTTON 3 (-->)
    bPressed = true;  //Button was pressed
    if(gotAns) {    //If there was an answer
        onReset();  //Reset all variables to default value
        lcd.clear();//Clears the LCD screen
    }

    if(displayNum != 9){  //While the current displayed number isn't 9
      displayNum++;       //Add 1 5 --> 6 --> 7 ...
    }

    lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
    lcd.print(displayNum);      //Displaying the number on the LCD
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b4state == 1 && time >= future && !bPressed){  //BUTTON 4 (+)
    bPressed = true;  //Button was pressed
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;  //going back 1 position to override the previous operation shown on LCD
    }
    else {  //User did not press another operation
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {          //If answer was obtained
      lcd.clear();        //Clear the LCD screen
      lcd.setCursor(0,1); //Cursor to bottom left
      lcd.print(ans);     //Prints the answer
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans");   //Prints Ans
      posCursor = 3;      //Setting cursor position to 3 columns over
    }

    if(posCursor-opPos > 1 && operation != 0) //Operation pressed after secNum
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();          //Solving current equation
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans+");  //Prints Ans+
      operation = 1;      //Setting operation to 1 (plus)
      posCursor = 4;      //Setting cursor position to 4 columns over
    }
    else {  //No operation was pressed after second number
      opPos = posCursor;  //Setting the operation position to current cursor position
      lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
      lcd.print("+");   //Printing the plus sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 1;  //Setting operation to 1 for addition 
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b5state == 1 && time >= future && !bPressed){  //BUTTON 5 (-)
    bPressed = true;  //Button was pressed 
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;  //going back 1 position to override the previous operation shown on LCD
    }
    else {  //User did not press another operation
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {          //If answer was obtained
      lcd.clear();        //Clear the LCD screen
      lcd.setCursor(0,1); //Cursor to bottom left
      lcd.print(ans);     //Prints the answer
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans");   //Prints Ans
      posCursor = 3;      //Setting cursor position to 3 columns over
    }

    if(posCursor-opPos > 1 && operation != 0) //Operation pressed after secNum
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();          //Solving current equation
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans-");  //Prints Ans-
      operation = 2;      //Setting operation to 2 (minus)
      posCursor = 4;      //Setting cursor position to 4 columns over
    }
    else {  //No operation was pressed after second number
      opPos = posCursor;  //Setting the operation position to current cursor position
      lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
      lcd.print("-");   //Printing the minus sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 2;  //Setting operation to 2 for subtraction
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b6state == 1 && time >= future && !bPressed){  //BUTTON 6 (x)
    bPressed = true;  //Button was pressed
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;  //going back 1 position to override the previous operation shown on LCD
    }
    else {  //User did not press another operation
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {          //If answer was obtained
      lcd.clear();        //Clear the LCD screen
      lcd.setCursor(0,1); //Cursor to bottom left
      lcd.print(ans);     //Prints the answer
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans");   //Prints Ans
      posCursor = 3;      //Setting cursor position to 3 columns over
    }

    if(posCursor-opPos > 1 && operation != 0) //Operation pressed after secNum
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();          //Solving current equation
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ansx");  //Prints Ansx
      operation = 3;      //Setting operation to 3 (times)
      posCursor = 4;      //Setting cursor position to 4 columns over
    }
    else {  //No operation was pressed after second number
      opPos = posCursor;  //Setting the operation position to current cursor position
      lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
      lcd.print("x");   //Printing the times sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 3;  //Setting operation to 3 for multiplication
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b7state == 1 && time >= future && !bPressed){  //BUTTON 7 (/)
    bPressed = true; //Button was pressed
    if(operation != 0 && (posCursor-opPos <= 1)) {  //User pressed another operation
      posCursor--;  //going back 1 position to override the previous operation shown on LCD
    }
    else {  //User did not press another operation
      firstNum = currNum; //Setting the first number to the current number obtained
      currNum = 0;  //Resetting currNum to 0 for second number
    }
    
    if(gotAns) {          //If answer was obtained
      lcd.clear();        //Clear the LCD screen
      lcd.setCursor(0,1); //Cursor to bottom left
      lcd.print(ans);     //Prints the answer
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans");   //Prints Ans
      posCursor = 3;      //Setting cursor position to 3 columns over
    }

    if(posCursor-opPos > 1 && operation != 0) //Operation pressed after secNum
    {
      currNum = currNum * 10 + displayNum;  //Getting the current number
      onSecOp();          //Solving current equation
      gotAns = false;     //Reset gotAns to false
      firstNum = ans;     //Setting first number equal to answer
      lcd.setCursor(0, 0);//Cursor to top left
      lcd.print("Ans/");  //Prints Ans/
      operation = 4;      //Setting operation to 4 (divide)
      posCursor = 4;      //Setting cursor position to 4 columns over
    }
    else {  //No operation was pressed after second number
      opPos = posCursor;  //Setting the operation position to current cursor position
      lcd.setCursor(posCursor,0); //Setting the cursor of the LCD
      lcd.print("/");   //Printing the divide sign
      posCursor++;  //Adding a column to the cursor position
    }
    operation = 4;  //Setting operation to 4 for division
    future = time + 250;  //Prevents user from pressing button for 1/4 sec
  }
  else if(b8state == 1 && time >= future && !bPressed){  //BUTTON 8 (=)
    bPressed = true;  //Button was pressed
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
    bPressed = false; //Setting bPressed to false
  }
}

/**
 * @brief Get the frequency to play on the buzzer
 * @param currentNum 
 * @return int 
 */
int getTone(int currentNum) {
  //The states of the buttons
  int b1state = digitalRead(b1);
  int b2state = digitalRead(b2);
  int b3state = digitalRead(b3);
  int b4state = digitalRead(b4);
  int b5state = digitalRead(b5);
  int b6state = digitalRead(b6);
  int b7state = digitalRead(b7);
  int b8state = digitalRead(b8);

  if(b1state == 1 || b3state == 1) {
    if(currentNum == 0)
      return 440; //A
    else if(currentNum == 1)
      return 466; //A#
    else if(currentNum == 2)
      return 493; //B
    else if(currentNum == 3)
      return 523; //C
    else if(currentNum == 4)
      return 554; //C#
    else if(currentNum == 5)
      return 587; //D
    else if(currentNum == 6)
      return 622; //D#
    else if(currentNum == 7)
      return 659; //E
    else if(currentNum == 8)
      return 698; //F
    else if(currentNum == 9)
      return 739; //F#
  }
  else if(b2state == 1)
    return 783;   //G 
  else if(b4state == 1)
    return 830;   //G#
  else if(b5state == 1)
    return 880;   //A
  else if(b6state == 1)
    return 932;   //A#
  else if(b7state == 1)
    return 987;   //B
  else if(b8state == 1)
    return 1046;  //C
  else
    return 0;     //SILENCE
}

/**
 * @brief Resets variable values to default value
 */
void onReset() {
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

/**
 * @brief Method will be called when a second operation is pressed 
 *        after a second number is created.
 *        Ex:  20 + 45 -
 *  >>>   firtNum: 20, operation: 1, secNum: 45 (Second operation pressed)
 */
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

/**
 * @brief Will  blink the current number displayed, @param num, every 1/2 sec
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

/**
 * @brief Will play a @param tone on @param buzzer every 1/2 second
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

/**
 * @brief Checks the button state
 */
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
