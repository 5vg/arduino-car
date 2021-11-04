//adds servo library
#include <Servo.h>

//initialises servos
Servo servo;
Servo servo2;

//sets pins and variables to be used in code
int motorPins[] = {6, 7};
int noOfMotorPins = sizeof(motorPins)/sizeof(int);
int Speed; //Variable to store Speed, by defaul 0 PWM
int incoming = 0;
int x = 1;
int lenOfNote;

//starting melody function
void melody(){
  //holds the frequency values for the melody
  int actualMelody[] = { 466, 370, 370, 329, 370, 370, 370, 329, 370, 370, 370, 466, 0, 466, 554, 493, 554, 622, 740, 740, 831, 740, 370, 370, 415, 370, 466, 415, 415, 370, 415, 415, 466, 311, 311 };
  //holds the tone length values of the melody
  int toneLength[] = { 8, 4, 16, 16, 8, 4, 16, 16, 8, 4, 4, 4, 16, 4, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4, 4, 4, 8, 8, 8, 2, 8 };
  int melodyLength = sizeof(actualMelody)/2; //finds length of melody
  for(int i=0; i<melodyLength; i++){//plays the melody note by note
    lenOfNote = 1200/toneLength[i];
    tone(8, actualMelody[i], lenOfNote);
    delay(lenOfNote*1.3);
    noTone(8);
    delay(50);
  }
}

void setup()
{
//sets up the motors, servos and initialises serial communication
  for(int i = 0; i<noOfMotorPins; i++){
    pinMode(motorPins[i], OUTPUT);
  }
  melody(); //plays melody
  Serial.begin(9600); 
  servo.attach(4);
  servo2.attach(5);
  servo.write(45); //sets servos to their intitial position
  servo2.write(45);
}

void loop()
{ 
//checks for serial communication
  if (Serial.available() > 0)
  { 
    //reads the incoming communication and acts accordingly
    //(by either starting the motors, stopping them or moving the servos
    incoming = Serial.read();
    if(incoming == 'b'){
      analogWrite(motorPins[0], 0);
      analogWrite(motorPins[1], 0);
    }
    else if(incoming == 'l'){
      analogWrite(motorPins[0], 250);
      analogWrite(motorPins[1], 0);
    }
    
    else if(incoming == 'f'){
      analogWrite(motorPins[0], 250);
      analogWrite(motorPins[1], 250);
    }
    else if(incoming == 'r'){
      analogWrite(motorPins[0], 0);
      analogWrite(motorPins[1], 250);
    }
    else if(incoming == 's'){
      Serial.print(x);
      if(x!=0){
        servo.write(90);
        servo2.write(90);
        x = 0;
      }else{
        servo.write(45);
        servo2.write(45);
        x = 1;
      }
    }
  }
}
