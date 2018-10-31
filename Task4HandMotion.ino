//#include <Servo.h>
#include <Keypad.h>
#include <Stepper.h>

//KeyPad declarations
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
//from right to left A3,A2,A1,A0,2,3,4,5
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A0, A1, A2, A3}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Stepper declarations
const int stepsPerRevolution = 20;
Stepper finger1(stepsPerRevolution, 2,3,4,5);
int fing1Pos=0,fing2Pos=0;                 // Actual steppers positions(0-4096)->(0-360°)
/*
Servo finger1;
Servo finger2;
*/
int fing1Up = 0; //assign to 1 in Keypad
int fing1Mid = 0; //assign to 4 in Keypad
int fing1Bottom = 0; //assign to 7 in Keypad
int fing2Up = 0; //assign to 2 in Keypad
int fing2Mid = 0; //assign to 5 in Keypad
int fing2Bottom = 0; //assign to 8 in Keypad

void setup() {  
  Serial.begin(9600);
  //finger1.attach(3);
  //finger2.attach(4);
   finger1.setSpeed(200);
   
  /*pinMode(fing1Up, INPUT);
  pinMode(fing1Mid, INPUT);
  pinMode(fing1Bottom, INPUT);
  pinMode(fing2Up, INPUT);
  pinMode(fing2Mid, INPUT);
  pinMode(fing2Bottom, INPUT);*/
}

void loop() {
  // put your main code here, to run repeatedly:
  /*if(fing1Up == HIGH && fing1Mid == HIGH && fing1Bottom == HIGH)
  {
      C=1;//sending to C#
      finger1.write(90);
  }*/
  char key = keypad.getKey();
  
  if (key){
   if(key == '1') { fing1Up = 1; goToPos(180); Serial.println(fing1Pos);}
   if(key == '4') { fing1Mid = 1; goToPos(270);Serial.println(fing1Pos);}
   if(key == '7') { fing1Bottom = 1;goToPos(360);Serial.println(fing1Pos);}
   if(key == '2') { fing2Bottom = 1; }
   if(key == '5') { fing2Bottom = 1; }
   if(key == '8') { fing2Bottom = 1; }
  }
  
}
void goToPos(int newPos)
{
  //to goto certain position by finger1 stepper motor
  int diff = newPos - fing1Pos; int stepNo;
  if(diff == 0)
    return;
  else if (diff > 0)
  {
    stepNo = 1;
    while(fing1Pos < newPos)
    {
      finger1.step(stepNo);
      fing1Pos++;
    }
  }
  else
  {
    stepNo = -1;
    while(fing1Pos > newPos)
    {
      finger1.step(stepNo);
      fing1Pos--;
    } 
  }
}
