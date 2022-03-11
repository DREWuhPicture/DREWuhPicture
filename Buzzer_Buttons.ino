//Made by DREWuhPicture

#define numButtons 6

//Define pins
byte button[] = {1, 2, 4, 6, 8, 10};
byte led[] = {0, 3, 5, 7, 9, 11};
#define buzzer 12
#define indicator 13
#define resetButton 14

boolean flag = false;
byte countdown = numButtons - 1;
boolean buttonState[numButtons];

void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(indicator, OUTPUT);
  pinMode(resetButton, INPUT_PULLUP);
  for (int i = 0; i < numButtons; i++){
    pinMode(button[i], INPUT_PULLUP);
    pinMode(led[i], OUTPUT);
    buttonState[i] = false;
  }

  doubleFlash();
  digitalWrite(indicator, HIGH);
}

void loop() {
  //check for reset if exited the sweeping loop
  if (digitalRead(resetButton) == LOW)
    reset();
  
  //Sweep until someone pushes a button AND, once pushed, check the other buttons one last time
  while (countdown > 0){
    for (int i = 0; i < numButtons; i++){
      if (countdown > 0){
        if(flag){
          countdown--;
        }
        if (digitalRead(button[i]) == LOW){
          buttonState[i] = true;
          flag = true;
          digitalWrite(buzzer, HIGH);
        }
      }
    }
  }
  
  //Illuminate the winning LED(s)
  for (int i = 0; i < numButtons; i++){
    if (buttonState[i] == true){
      digitalWrite(led[i], HIGH);
    }
  }
  
  //Turn on buzzer for as long as the winning person(s) holds their button(s) down
  if (flag){
    digitalWrite(indicator, LOW);
    boolean temp = false;
    for (int i = 0; i < numButtons; i++){
      if (buttonState[i]){
        if (digitalRead(button[i]) == LOW)
          temp = true;
      }
    }
    if (!temp){
      flag = false;
      digitalWrite(buzzer, LOW);
    }
  }
}

void reset(){
  digitalWrite(indicator, LOW);
  allOff();

  //Actual important shit to reset
  flag = false;
  countdown = numButtons - 1;
  for (int i = 0; i < numButtons; i++){
    buttonState[i] = false;
  }

  //wait until button is released, then flash lights to show reset is complete
  while (digitalRead(resetButton) == LOW){}
  doubleFlash();
  digitalWrite(indicator, HIGH);
}

void doubleFlash(){
  allOn();
  delay(100);
  allOff();
  delay(100);
  allOn();
  delay(100);
  allOff();
}

void allOn(){
  for (int i = 0; i < numButtons; i++){
    digitalWrite(led[i], HIGH);
  }
}

void allOff(){
  for (int i = 0; i < numButtons; i++){
    digitalWrite(led[i], LOW);
  }
}
