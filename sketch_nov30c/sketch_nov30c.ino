#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const byte ROWS = 4; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
const String correctPassword = "1234";
String enteredPassword = "";
const int ledPin = 3;
const int buzzerPin = 4;
const int motorPin = 5;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter Password:");

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motorPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(motorPin, LOW);
}

void loop() {
  char key = keypad.getKey(); 

  if (key) {
    if (key == '#') { 
      lcd.clear();
      if (enteredPassword == correctPassword) {
        lcd.print("Valid password.");
        lcd.setCursor(0, 1);
        lcd.print("Door Unlocked");
        digitalWrite(ledPin, HIGH); 
        digitalWrite(motorPin, HIGH); 
        delay(3000); 
        digitalWrite(ledPin, LOW); 
        digitalWrite(motorPin, LOW); 
        lcd.clear();
        lcd.print("Door Locked");
      } else {
        lcd.print("Invalid Password");
        lcd.setCursor(0, 1);
        lcd.print("Blocked!!");
        digitalWrite(buzzerPin, HIGH); 
        delay(3000); 
        digitalWrite(buzzerPin, LOW); 
      }
      enteredPassword = ""; 
      delay(2000); 
      lcd.clear();
      lcd.print("Enter Password:");
    } else if (key == '*') { 
      enteredPassword = "";
      lcd.clear();
      lcd.print("Enter Password:");
    } else {
      enteredPassword += key;
      lcd.setCursor(enteredPassword.length() - 1, 1);
      lcd.print("*");
    }
  }
}
