#include <Servo.h>

// Definicije pinova
const int servoPin    = 9;  // Servo motor spojen na pin 9
const int button1Pin  = 2;  // Tipkalo za povećanje kuta (rotacija u jednom smjeru)
const int button2Pin  = 3;  // Tipkalo za smanjenje kuta (rotacija u suprotnom smjeru)

// Debounce kašnjenje u milisekundama
const int debounceDelay = 50;

Servo myServo;
int currentAngle = 0;  // Početni kut (0°)

void setup() {
  myServo.attach(servoPin);
  // Postavljamo tipkala, koristeći interne pull-up otpornike:
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  
  // Inicijalno postavljanje servo motora
  myServo.write(currentAngle);
}

void loop() {
  // Čitamo stanja tipkala (s obzirom da su u INPUT_PULLUP načinu, nepregnuta stanja su HIGH,
  // a kada se tipkalo pritisne, pin ide u LOW stanje)
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);
  
  // Ako su oba tipkala pritisnuta, resetiraj servo na 0°
  if (button1State == LOW && button2State == LOW) {
    currentAngle = 0;
    myServo.write(currentAngle);
    delay(debounceDelay);
    // Čekamo dok se oba tipkala ne otpuste
    while(digitalRead(button1Pin) == LOW || digitalRead(button2Pin) == LOW);
    delay(debounceDelay);
  }
  // Ako je pritisnuto samo tipkalo 1 (povećanje kuta)
  else if (button1State == LOW) {
    if (currentAngle < 180) {
      currentAngle += 10;
    }
    myServo.write(currentAngle);
    delay(debounceDelay);
    // Čekamo dok se tipkalo ne otpusti
    while(digitalRead(button1Pin) == LOW);
    delay(debounceDelay);
  }
  // Ako je pritisnuto samo tipkalo 2 (smanjenje kuta)
  else if (button2State == LOW) {
    if (currentAngle > 0) {
        currentAngle -= 10;
    }
    myServo.write(currentAngle);
    delay(debounceDelay);
    // Čekamo dok se tipkalo ne otpusti
    while(digitalRead(button2Pin) == LOW);
    delay(debounceDelay);
  }
}
