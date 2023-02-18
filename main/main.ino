#include <LiquidCrystal.h>

// Rotary Encoder Pins
#define encoderPinA 3
#define encoderPinB 4

// Button Pins
#define buttonPin 2

// LCD Pins
#define rs 13
#define en 12
#define d4 11
#define d5 10
#define d6 9
#define d7 8

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

volatile int encoderPos = 0;
int lastEncoderPos = 0;

float gearDiameterInMM = 13.0;
int pulsesPerRevolution = 30;

void setup() {
  Serial.begin(9600);

  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, RISING);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcdPrintPosition(0);
}

void encoderInterrupt() {
  if (digitalRead(encoderPinA) == digitalRead(encoderPinB)) {
    encoderPos++;
  } else {
    encoderPos--;
  }
}

void buttonInterrupt() {
  encoderPos = 0;
}

void loop() {
  // Get the current position incase it changes midway through the loop
  int currentEncoderPos = encoderPos;

  if (lastEncoderPos != currentEncoderPos) {
    Serial.println(positionToValueMM(currentEncoderPos));

    lcdPrintPosition(currentEncoderPos);

    lastEncoderPos = currentEncoderPos;
  }
}

float positionToValueMM(int position) {
  return (float)position * circumferenceFromDiameter(gearDiameterInMM) / pulsesPerRevolution;
}

float circumferenceFromDiameter(float diameter) {
  return diameter * 3.14159;
}

float mmToInch(float measurement) {
  return measurement * 0.03937;
}

void lcdPrintPosition(float position) {
  float positionInMM = positionToValueMM(position);
  lcd.clear();

  lcd.print(String(positionInMM, 3));
  lcd.print(" mm");

  lcd.setCursor(0, 1);
  lcd.print(String(mmToInch(positionInMM), 3));
  lcd.print(" in");
}