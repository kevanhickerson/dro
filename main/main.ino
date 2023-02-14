#define encoderPinA 3
#define encoderPinB 4
#define buttonPin 2

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