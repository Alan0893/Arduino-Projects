//CONSTANTS
const int SETUP_TIME = 5000;
const int AUTONOMOUS_TIME = 15000;
const int STOP_TIME = 2000;

const int MOTOR_POWER = 200;
const int LIGHT_AMT = 800;

//MOTOR 1
int forward, backward;

//MOTOR 2
int forward2, backward2;

//PHOTORESISTORS
int lightF, lightR, lightL, lightB;

// FLEXSENSORS
int f1, f2;

void setup() {
    Serial.begin(9600);

    //MOTOR 1 
    forward = 10;
    backward = 11;
    pinMode(forward, OUTPUT);
    pinMode(backward, OUTPUT);

    //MOTOR 2
    forward2 = 5;
    backward2 = 6;
    pinMode(forward2, OUTPUT);
    pinMode(backward2, OUTPUT);

    //PHOTORESISTORS
    lightF = A0;
    lightR = A1;
    lightL = A2;
    lightB = A5;
    pinMode(lightF, INPUT);
    pinMode(lightR, INPUT);
    pinMode(lightL, INPUT);
    pinMode(lightB, INPUT);

    //FLEXSENSORS
    f1 = A3;//right
    f2 = A4;
    pinMode(f1, INPUT);
    pinMode(f2, INPUT);
}

//============================================================
//DO NOT WRITE CODE IN THE LOOP METHOD.
void loop() {
    //DO NOT TOUCH THIS CODE
    /*long mil = millis();
      if(mil<SETUP_TIME) {
        //LEAVE THIS BLANK
    }
    else if(mil<AUTONOMOUS_TIME+SETUP_TIME) {
        autonomousMode();
    }
    else if(mil<AUTONOMOUS_TIME+SETUP_TIME+STOP_TIME) {
        fullStop();
    }
    else {
        teleOpMode();
    }*/
    teleOpMode();
    testSensors();
}
//============================================================

//WRITE CODE IN HERE:  YOUR AUTONOMOUS CODE GOES IN HERE.  PART 1 OF RACE
void autonomousMode(){
  int rightFlex = analogRead(f1); //right
  int leftFlex = analogRead(f2);

  long time = millis();

  if(time < 15000)
  {
  if(rightFlex < 925 && leftFlex < 850)
  {
    analogWrite(forward, 200);
    analogWrite(backward, 0);

    analogWrite(forward2, 180);
    analogWrite(backward2, 0);
  }
  else if(rightFlex > 925 && leftFlex < 850)
  {
    analogWrite(forward, MOTOR_POWER);
    analogWrite(backward, 0);

    analogWrite(forward2, 0);
    analogWrite(backward2, 180);
  }
  else if(rightFlex < 925 && leftFlex > 850)
  {
    analogWrite(forward, 0);
    analogWrite(backward, MOTOR_POWER);

    analogWrite(forward2, 180);
    analogWrite(backward2, 0);
  }
  else if(rightFlex > 925 && leftFlex > 850)
  {
    analogWrite(forward, MOTOR_POWER);
    analogWrite(backward, 0);

    analogWrite(forward2, 0);
    analogWrite(backward2, 180);
  }
  }
  else if(time >= 15000)
  {
    if(time < 15800)
    {
       analogWrite(forward, 0);
       analogWrite(backward, MOTOR_POWER);
    
       analogWrite(forward2, 180);
       analogWrite(backward2, 0);
    }
    else if(time >= 15800)
    {
      analogWrite(forward, 200);
      analogWrite(backward, 0);
  
      analogWrite(forward2, 180);
      analogWrite(backward2, 0);
    }
  }
}

//WRITE CODE IN HERE:  YOUR TELEOP CODE GOES IN HERE.  PART 2 OF RACE
//you MUST write this method
void teleOpMode() {
    int lightFState = analogRead(lightF);
    int lightRState = analogRead(lightR);
    int lightLState = analogRead(lightL);
    int lightBState = analogRead(lightB);

    int val = greatestOf4();
    if (val == 1) {
        analogWrite(forward, 170);
        analogWrite(backward, 0);

        analogWrite(forward2, 150);
        analogWrite(backward2, 0);
    }
    else if (val == 2) {
        analogWrite(forward, 170);
        analogWrite(backward, 0);

        analogWrite(forward2, 0);
        analogWrite(backward2, 150);
    }
    else if (val == 3) {
        analogWrite(forward, 0);
        analogWrite(backward, 170);

        analogWrite(forward2, 150);
        analogWrite(backward2, 0);    
    }
    else if (val == 4) {
        analogWrite(forward, 0);
        analogWrite(backward, 170);

        analogWrite(forward2, 0);
        analogWrite(backward2, 150);
    }
    else if (val == 5) {
        fullStop();
    }
}
//WRITE CODE IN HERE:  YOU SHOULD MAKE EVERY MOTOR STOP 
//you MUST write this method
void fullStop(){
    //MOTOR 1 
    analogWrite(forward, 0);
    analogWrite(backward, 0);
    //MOTOR 2
    analogWrite(forward2, 0);
    analogWrite(backward2, 0);
}

//GETS WHICH DIRECTION THE CAR SHOULD GO
int greatestOf4()
{
    int forward = analogRead(lightF); // 1
    int right = analogRead(lightR); // 2
    int left = analogRead(lightL); // 3
    int back = analogRead(lightB); // 4

    if ((forward < LIGHT_AMT) && (right < LIGHT_AMT) && (left < LIGHT_AMT) && (back < LIGHT_AMT))
        return 5;
    else if ((forward > right) && (forward > left) && (forward > back))
        return 1;
    else if ((right > forward) && (right > left) && (right > back))
        return 2;
    else if ((left > forward) && (left > right) && (left > back))
        return 3;
    else if ((back > forward) && (back > right) && (back > left))
        return 4;
}

// TESTING THE SENSORS (PHOTORESISTORS & FLEXSENSORS)
void testSensors()
{
    int lightFState = analogRead(lightF);
    int lightRState = analogRead(lightR);
    int lightLState = analogRead(lightL);
    int lightBState = analogRead(lightB);

    int f1State = analogRead(f1);
    int f2State = analogRead(f2);

    Serial.print("lightF = ");
    Serial.print(lightFState);
    Serial.print("                  lightR = ");
    Serial.print(lightRState);
    Serial.print("                  lightL = ");
    Serial.print(lightLState);
    Serial.print("                  lightB = ");
    Serial.print(lightBState);

    Serial.print("                  f1 = ");
    Serial.print(f1State);
    Serial.print("                  f2 = ");
    Serial.println(f2State);
}
