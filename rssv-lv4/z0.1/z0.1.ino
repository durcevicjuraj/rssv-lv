const int led1Pin = 8;
const int led2Pin = 9;
const int buttonPin = 2; 

const int numLevels = 3;
unsigned long blinkPeriods[numLevels] = {1000, 500, 250};
int currentLevel = 0;

unsigned long lastToggleTime = 0;
bool ledState = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  bool buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    currentLevel = (currentLevel + 1) % numLevels;
    delay(50);  
  }
  lastButtonState = buttonState;

  unsigned long currentMillis = millis();
  unsigned long interval = blinkPeriods[currentLevel];

  if (currentMillis - lastToggleTime >= interval) {
    lastToggleTime = currentMillis;
    ledState = !ledState;

    if (ledState) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
    } else {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    }
  }
}


// Sa interruptom

/*
const int led1Pin = 8;
const int led2Pin = 9;
const int buttonPin = 2; 

const int numLevels = 3;
unsigned long blinkPeriods[numLevels] = {1000, 500, 250};

// Varijable koje se ažuriraju unutar ISR-a moraju biti deklarirane kao volatile
volatile int currentLevel = 0;
volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50;  // debounce interval u milisekundama

unsigned long lastToggleTime = 0;
bool ledState = false;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Postavljanje prekida na pin 2 (buttonPin) na padajućem rubu
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
}

void loop() {
  unsigned long currentMillis = millis();
  // Dohvatimo period bljeskanja prema trenutačnoj razini (currentLevel)
  unsigned long interval = blinkPeriods[currentLevel];
  
  // Provjera proteklog vremena i prebacivanje stanja LED-a
  if (currentMillis - lastToggleTime >= interval) {
    lastToggleTime = currentMillis;
    ledState = !ledState;

    if (ledState) {
      digitalWrite(led1Pin, HIGH);
      digitalWrite(led2Pin, LOW);
    } else {
      digitalWrite(led1Pin, LOW);
      digitalWrite(led2Pin, HIGH);
    }
  }
}

// ISR funkcija za tipkalo
void buttonISR() {
  // Debounce: provjeri proteklo vrijeme od posljednjeg prekida
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > debounceDelay) {
    // Povećaj razinu (ciklički: 0, 1, 2, pa ponovno 0)
    currentLevel = (currentLevel + 1) % numLevels;
    lastInterruptTime = interruptTime;
  }
}

*/