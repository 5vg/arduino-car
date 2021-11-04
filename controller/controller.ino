//sets pins and variables to be used in 
int controlButtons[] = {2 , 3, 4, 5, 6};
int noOfButtons = sizeof(controlButtons)/sizeof(int);
int buttonState;
int LEDPins[] = {7,8};

//sets all buttons as input devices
void buttonSetup(void){
  for (int i = 0; i<noOfButtons; i++){
    pinMode(controlButtons[i], INPUT);
  }
}

//sets all LEDs as output devices
void LEDSetup(void){
  for (int i=0; i<2; i++){
    pinMode(LEDPins[i], OUTPUT);
  }
}

//sets LED postions when car is in motion
void carDrive(void){
  digitalWrite(LEDPins[0], HIGH);
  digitalWrite(LEDPins[1], LOW);
}

//sets LED positions when car is stopped
void carStop(void){
  digitalWrite(LEDPins[0], HIGH);
  digitalWrite(LEDPins[1], LOW);
}

//sets up the buttons, the LEDs, begins serial communication and lights the LEDs to be indicative of the car's current state
void setup() {
  buttonSetup();
  LEDSetup();
  Serial.begin(9600);
  carStop();
}

//loop starts by setting up 'high' variable to hold the value of the pin where there is a button pressed
void loop() {
  int high = 0;
  //for loop checks which button is pressed (if there is one) and sets the 'high' variable accordingly
  for (int j=0; j < noOfButtons; j++){
    buttonState = digitalRead(controlButtons[j]);
    if (buttonState == LOW){
      high = j+2;
      break;
    }
  }
  // checks if high is 0. if it is, the car stays at its current state
  if(high != 0){
    if(high == 2){
      //if the left button is pressed, sends the letter l via serial communication
      Serial.write("l");
      carDrive();
    }
    else if(high == 3){
      //if the forward button is pressed, send the letter f via serial communication 
      Serial.write("f");
      carStop();
    }
    else if(high == 4){
      //if the stop button is pressed, send the letter b via serial communication
      Serial.write("b");
      carStop();
    }
    else if(high == 5){
      //if the right button is pressed, sends the letter r via serial communication 
      Serial.write("r");
      carStop();
    }
    else if(high == 6){
      //if the servo actuation switch is pressed, send the letter s via serial communcation
      Serial.write("s");
    }
  }
}
