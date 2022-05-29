//LEDS
int led13, led12, led11, led10, led9, led8, led7, 
	led6, led5, led4, led3, led2, led1, led0, 
	ledA0, ledA1, ledA2, ledA3, ledA4, ledA5;

long wWin;
//BOOLEANS
boolean countdown = true;
boolean go = true;
boolean win = false;

//SCORES
long scoreL = 0;
long scoreR = 0;

void setup()
{
  //LED Names corresponds to their PINs
  led13 = 13;
  led12 = 12;
  led11 = 11;
  led10 = 10;
  led9 = 9;
  led8 = 8;
  led7 = 7;
  led6 = 6;
  led5 = 5;
  led4 = 4;
  led3 = 3;
  led2 = 2;
  led1 = 1;
  led0 = 0;
  ledA0 = A0;
  ledA1 = A1;
  ledA2 = A2;
  ledA3 = A3;
  ledA4 = A4;
  ledA5 = A5;
  
  wWin = 0;
  
  pinMode(led13, OUTPUT);
  pinMode(led12, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led0, OUTPUT);
  pinMode(ledA0, OUTPUT);
  pinMode(ledA1, OUTPUT);
  pinMode(ledA2, OUTPUT);
  pinMode(ledA3, OUTPUT);
  pinMode(ledA4, OUTPUT);
  pinMode(ledA5, OUTPUT);
}

void loop()
{
  /*
  //TIME & SECONDS
  long time = millis();
  time-= wWin;
  long sec = time/100;

  if(sec < 5)//SEC < 5, begin countdown from 3-1
  	countdownBegin(sec);
  else if(sec == 5)//SEC = 5, Scoreboard appears at 0-0
    viewScore();
  else//SEC > 5, show incremented version of scoreboard
  {
    viewScore();//shows the scoreboard
    if(sec%2 == 0)//stops
      go = true;
    else if(sec%2 == 1 && go)//Increments 1 to either side and stops
    {
      increment1();//Increments 1
      go = false;//stops at next second
    }    
  }
  
  //WIN CONDITION
  if(scoreL == 9)//Left side wins
  {
    win = true;//win condition was met
    blinkL9();//starts to blink left side
    whenWin();
  }
  else if(scoreR == 9)//Right side wins
  {
    win = true;//win condition was met
    blinkR9();//starts to blink right side
 	whenWin();
  }
  */ allOn();
}

void whenWin()
{
  
  scoreL = 0;
  scoreR = 0;
  
}

//Method for slowly dimming out the light
void curveDim(int led)
{
  long time = millis();
  int power = 127.5*sin(2*PI*time/2000) + 127.5;
  if(power > 0)
  	analogWrite(led, power);
  else
    analogWrite(led, 0);
}
              
/*Method will create a countdown from 3-1 in the beginning
With the #1 being dimmed out at the end*/
void countdownBegin(long sec)
{
  //long time = millis();
  //long sec = time/1000;

  if(sec%5 == 0 && countdown == true)
    makeR3();
  else if(sec%5 == 1 && countdown == true)
    makeR2();
  else if(sec%5 == 2 && countdown == true)
    makeR1();
  else if(sec%5 == 3 && countdown == true)
  {
    curveDim(led3);
    curveDim(led6);
    curveDim(led5);
  }
  else if(sec < 5)
  {
    countdown = false;
    analogWrite(led3, 0);
    analogWrite(led6, 0);
    analogWrite(led5, 0);
  }
}

//Will increment a score of 1 to either side randomly
void increment1()
{ 
  long rand = random(0,2);
  
  if(rand == 0 && scoreL != 9 && scoreR != 9)//LEFT
  {
    scoreL++;
  }
  else if(rand == 1 && scoreR != 9 && scoreL != 9)//RIGHT
  {
    scoreR++;
  }
}

/*Creates a scoreboard. Lights up both sides of the scoreboard.
Beginning should be 0-0. Ends when either side reaches 9.*/
void viewScore()
{
  //LEFT SIDE OF SCOREBOARD
  if(scoreL == 0)
    makeL0();
  else if(scoreL == 1)
    makeL1();
  else if(scoreL == 2)
    makeL2();
  else if(scoreL == 3)
    makeL3();
  else if(scoreL == 4)
    makeL4();
  else if(scoreL == 5)
    makeL5();
  else if(scoreL == 6)
    makeL6();
  else if(scoreL == 7)
    makeL7();
  else if(scoreL == 8)
    makeL8();
  else if(scoreL == 9)
    makeL9();
  
  //RIGHT SIDE OF SCOREBOARD
  if(scoreR == 0)
    makeR0();
  else if(scoreR == 1)
    makeR1();
  else if(scoreR == 2)
    makeR2();
  else if(scoreR == 3)
    makeR3();
  else if(scoreR == 4)
    makeR4();
  else if(scoreR == 5)
    makeR5();
  else if(scoreR == 6)
    makeR6();
  else if(scoreR == 7)
    makeR7();
  else if(scoreR == 8)
    makeR8();
  else if(scoreR == 9)
    makeR9();
}

//note: cannot use allOn or allOff within the makeXY() methods 
//as brightness is lowered
void makeR0()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,LOW);
  digitalWrite(ledA0,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}

void makeR1()
{
  digitalWrite(ledA3,LOW);
  digitalWrite(ledA4,LOW);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,LOW);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,LOW);
  digitalWrite(ledA5,LOW);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,LOW);
}

void makeR2()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,LOW);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,HIGH);
  digitalWrite(led5,LOW);
  digitalWrite(led0,HIGH);
}

void makeR3()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,LOW);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}

void makeR4()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,LOW);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,LOW);
}

void makeR5()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,LOW);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}

void makeR6()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,LOW);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}

void makeR7()

{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,LOW);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,LOW);
  digitalWrite(ledA5,LOW);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,LOW);
}

void makeR8()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}

void makeR9()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,LOW);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,LOW);
}
  
void makeL0()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led12,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led11,HIGH);
  digitalWrite(led9,LOW);
}

void makeL1()
{
  digitalWrite(led13,HIGH);
  digitalWrite(led12,HIGH);
  digitalWrite(led11,HIGH);
  digitalWrite(led10,LOW);
  digitalWrite(led8,LOW);
  digitalWrite(led7,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led9,LOW);
}

void makeL2()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,LOW);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led11,LOW);
  digitalWrite(led4,HIGH);
}

void makeL3()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,LOW);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,HIGH);
}

void makeL4()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,LOW);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,LOW);
}

void makeL5()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led12,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,HIGH);
}

void makeL6()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led12,LOW);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,HIGH);
}

void makeL7()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,LOW);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,LOW);
  digitalWrite(led9,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,LOW);
}

void makeL8()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,HIGH);
}

void makeL9()
{
  digitalWrite(led8,HIGH);
  digitalWrite(led10,HIGH);
  digitalWrite(led13,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led12,HIGH);
  digitalWrite(led1,HIGH);
  digitalWrite(led9,HIGH);
  digitalWrite(led2,LOW);
  digitalWrite(led11,HIGH);
  digitalWrite(led4,LOW);
}

//BOTH SIDES ARE TURNED ON
void allOn()
{
  digitalWrite(led13, HIGH);
  digitalWrite(led12, HIGH);
  digitalWrite(led11, HIGH);
  digitalWrite(led10, HIGH);
  digitalWrite(led9, HIGH);
  digitalWrite(led8, HIGH);
  digitalWrite(led7, HIGH);
  digitalWrite(led6, HIGH);
  digitalWrite(led5, HIGH);
  digitalWrite(led4, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led0, HIGH);
  digitalWrite(ledA0, HIGH);
  digitalWrite(ledA1, HIGH);
  digitalWrite(ledA2, HIGH);
  digitalWrite(ledA3, HIGH);
  digitalWrite(ledA4, HIGH);
  digitalWrite(ledA5, HIGH);
}
//BOTH SIDES ARE TURNED OFF
void allOff()
{
  digitalWrite(led13, LOW);
  digitalWrite(led12, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led10, LOW);
  digitalWrite(led9, LOW);
  digitalWrite(led8, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led0, LOW);
  digitalWrite(ledA0, LOW);
  digitalWrite(ledA1, LOW);
  digitalWrite(ledA2, LOW);
  digitalWrite(ledA3, LOW);
  digitalWrite(ledA4, LOW);
  digitalWrite(ledA5, LOW);
}

//ALL OFF ONE SIDE METHODS
void allOffL()
{
  digitalWrite(led8, LOW);
  digitalWrite(led10, LOW);
  digitalWrite(led13, LOW);
  digitalWrite(led7, LOW);
  digitalWrite(led12, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led9, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led11, LOW);
  digitalWrite(led4, LOW);
}

void allOffR()
{
  digitalWrite(ledA3, LOW);
  digitalWrite(ledA4, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(ledA2, LOW);
  digitalWrite(led6, LOW);
  digitalWrite(ledA1, LOW);
  digitalWrite(ledA5, LOW);
  digitalWrite(ledA0, LOW);
  digitalWrite(led5, LOW);
  digitalWrite(led0, LOW);
}

//Blinking Method: Activates on win
void blinkL9()
{
  long time = millis();
  long halfSec = time/500;
  
  if(halfSec%2 == 0)
    makeL9();
  else
    allOffL();
}
void blinkR9()
{
  long time = millis();
  long halfSec = time/500;
  
  if(halfSec%2 == 0)
    makeR9();
  else
    allOffR();
}
               
/*Templates for makeLY(),makeRY() digitalWrite statements are
in order from left to right, next row, left to right, etc. 
void makeLY()
{
  digitalWrite(led8,LOW);
  digitalWrite(led10,LOW);
  digitalWrite(led13,LOW);
  digitalWrite(led7,LOW);
  digitalWrite(led12,LOW);
  digitalWrite(led1,LOW);
  digitalWrite(led9,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led11,LOW);
  digitalWrite(led4,LOW);
}

void makeRX()
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledA4,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(ledA2,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(ledA1,HIGH);
  digitalWrite(ledA5,HIGH);
  digitalWrite(ledA0,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led0,HIGH);
}
*/
