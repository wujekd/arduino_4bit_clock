#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

const int ledPins[] = {8, 9, 10, 11}; // Replace with your actual pin numbers
const int analogIn = A0;            // Replace with your actual analog pin for speed control and start/stop
const int lBtn = 12;          // Replace with your actual pin number for left button
const int rBtn = 13; 


int index = 0;   
int speed = 500;
int mode = 1;
int play = 1;


const int binVal1[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
const int binVal2[] = {0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1};
const int binVal3[] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1};
const int binVal4[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1};



void setup() {

Serial.begin(9600);
lcd.begin(16, 2);
pinMode(lBtn, INPUT_PULLUP);

}


void setLeds(){
  if (binVal1[index] == 0) {
    digitalWrite(ledPins[0], LOW);
  } else {
    digitalWrite(ledPins[0], HIGH);
  }
  if (binVal2[index] == 0) {
    digitalWrite(ledPins[1], LOW);
  } else {
    digitalWrite(ledPins[1], HIGH);
  }
  if (binVal3[index] == 0) {
    digitalWrite(ledPins[2], LOW);
  } else {
    digitalWrite(ledPins[2], HIGH);
  }
  if (binVal4[index] == 0) {
    digitalWrite(ledPins[3], LOW);
  } else {
    digitalWrite(ledPins[3], HIGH);
  }
}

void screenUp() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("step:");

  lcd.print(index);
  lcd.setCursor(8, 0);
  if (analogRead(analogIn) < 1000){
    lcd.print("speed:");
    lcd.print(100 - (analogRead(analogIn) /10));
  } else {
    lcd.print("STOPPED");
  }

  // lcd.print('#');
  for (int i =0; i < index + 1; i++){
    // Serial.print(i);
    // delay(5);
    lcd.setCursor(i , 1);
    lcd.print("#");

  }
}

void loop() {
  Serial.println(analogRead(analogIn));
  if (digitalRead(lBtn) == LOW && digitalRead(rBtn) == LOW){
    lcd.clear();
    lcd.print("Czesc Mamo!");
    delay(3500);
    lcd.clear();


  }
  
  setLeds();
  screenUp();
  int speed = analogRead(analogIn) * 1.4;
  
  
  if (analogRead(analogIn) > 1001) {
    play = 0;
    if(digitalRead(lBtn) == LOW){
      index--;
    } else if(digitalRead(rBtn) == LOW){
      index++;
    }
    delay(200);

  } else {
    play = 1;
    if(digitalRead(lBtn) == LOW){
    mode = 2;
  } else if(digitalRead(rBtn) == LOW) {
    mode = 1;
  }
  delay(speed);
  }



  if(play != 0){
    if(mode ==1){
      index++;
    } else {
      index--;
    }
  }

if(index == 16){
  index = 0;
} else if(index == -1){
  index = 15;
}
}
