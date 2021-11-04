int controlButtons[] = {2 , 3, 4, 5};
int noOfButtons = sizeof(controlButtoms)/sizeof(int);

void buttonSetup(void){
  for (int i = 0; i<noOfButtons; i++){
    pinMode(controlButtons[i], INPUT);
  }
}

void setup() {
  buttonSetup()
  Serial.begin(9600)
}

void loop() {
  int high = 0;
  for (int i=0; i< noOfButtons; i++){
    buttonState = digitalRead(controlButtons[i]);
    if (buttonState == HIGH){
      high = i;
      break;
    }
  }
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if(high != 0){
    if(high == 2){
      //left
      Serial.write("L");
    }
    if(high == 3){
      //forward 
      Serial.write("F");
    }
    if(high == 4){
      //backward
      Serial.write("B");
    }
    if(high == 5){
      //right
      Serial.write("R");
    }
  }
}
