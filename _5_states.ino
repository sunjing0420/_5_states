int buttonPin = 5;
int potPin = A0;

int redLedPin = 11;
int blueLedPin = 10;
int greenLedPin = 9;

int ledVal = 0;
int potVal = 0;

int debounceWait = 5;

//state 0: off, 1: ON, 2: BLINK, 3: changing brightness, 4:one on
int state = 0;
unsigned long lastBlinkTime = 0;

void setup() {

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {

  potVal = analogRead(potPin);

  int oldButtonVal = digitalRead(buttonPin);
  delay(debounceWait);
  int newButtonVal = digitalRead(buttonPin);

  //see if the values are different
  if (oldButtonVal != newButtonVal) {

    if (newButtonVal == LOW) {
     
      state++;
     
      if (state > 4) {
      
        state = 0;
      }

      Serial.print("current state: ");
      Serial.println(state);

    } else {
      //this is our RISING edge (button up)
      //don't need right now
    }
  }

  if (state == 0) {

      digitalWrite(redLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
      digitalWrite(greenLedPin, LOW);

  } else if (state == 1) {

      digitalWrite(redLedPin, HIGH);
      digitalWrite(blueLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);

  } else if (state == 2 ){

    int blinkWaitTime = map(potVal, 0, 1023, 1000, 100);

    if (millis() - lastBlinkTime > blinkWaitTime) {
      if (ledVal == HIGH) {
        ledVal = LOW;
      } else {
        ledVal = HIGH;
      }

      lastBlinkTime = millis();
    }
      digitalWrite(redLedPin, ledVal);
      digitalWrite(blueLedPin, ledVal);
      digitalWrite(greenLedPin, ledVal);

  } else if (state == 3 ){

      ledVal = map(potVal, 0, 1023, 0, 255);

      analogWrite(redLedPin, ledVal);
      analogWrite(blueLedPin, ledVal);
      analogWrite(greenLedPin, ledVal);
  } else {

      int  ledOn = map(potVal, 0, 1023, 0, 300);
      
       if(ledOn>0&&ledOn<100){
           digitalWrite(redLedPin, LOW);
           digitalWrite(blueLedPin, LOW);
           digitalWrite(greenLedPin, HIGH);
       }else if(ledOn>100&&ledOn<200){
           digitalWrite(redLedPin, LOW);
           digitalWrite(blueLedPin, HIGH);
           digitalWrite(greenLedPin, LOW);
       }else{
           digitalWrite(redLedPin, HIGH);
           digitalWrite(blueLedPin, LOW);
           digitalWrite(greenLedPin, LOW);
       }
  }
}




