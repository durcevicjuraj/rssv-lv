const int redPin   = 9;
const int greenPin = 10;
const int bluePin  = 11;
const int buttonPin = 2;

int redValue   = 255;
int greenValue = 255;
int blueValue  = 255;

//https://forum.arduino.cc/t/debounce-time-code-explanation/1184674
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  setLED(redValue, greenValue, blueValue);
  randomSeed(analogRead(0));
}

void loop() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();
    
    if (inputChar == '1') {
      redValue = random(0, 256);
      Serial.print("Nova vrijednost crvene: ");
      Serial.println(redValue);
    } 
    else if (inputChar == '2') {
      greenValue = random(0, 256); 
      Serial.print("Nova vrijednost zelene: ");
      Serial.println(greenValue);
    } 
    else if (inputChar == '3') {
      blueValue = random(0, 256);  
      Serial.print("Nova vrijednost plave: ");
      Serial.println(blueValue);
    }
    
    setLED(redValue, greenValue, blueValue);
  }
  
  int buttonReading = digitalRead(buttonPin);
  
  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonReading == LOW) {
      redValue = 255;
      greenValue = 255;
      blueValue = 255;
      Serial.println("Reset sustava: Sve boje svijetle na maksimalnoj intenzitetu!");
      setLED(redValue, greenValue, blueValue);
    }
  }
  
  lastButtonState = buttonReading;
}

void setLED(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

// Isti kod pomocu interrupta

/*
const int redPin   = 9;
const int greenPin = 10;
const int bluePin  = 11;
const int buttonPin = 2;

int redValue   = 255;
int greenValue = 255;
int blueValue  = 255;


volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50; 

volatile bool resetFlag = false;

void resetISR();

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  setLED(redValue, greenValue, blueValue);
  randomSeed(analogRead(0));
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), resetISR, FALLING);
}

void loop() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();
    
    if (inputChar == '1') {
      redValue = random(0, 256);
      Serial.print("Nova vrijednost crvene: ");
      Serial.println(redValue);
    } 
    else if (inputChar == '2') {
      greenValue = random(0, 256);
      Serial.print("Nova vrijednost zelene: ");
      Serial.println(greenValue);
    } 
    else if (inputChar == '3') {
      blueValue = random(0, 256);
      Serial.print("Nova vrijednost plave: ");
      Serial.println(blueValue);
    }
    
    setLED(redValue, greenValue, blueValue);
  }
  
  if (resetFlag) {
    redValue   = 255;
    greenValue = 255;
    blueValue  = 255;
    Serial.println("Reset sustava: Sve boje svijetle na maksimalnom intenzitetu!");
    setLED(redValue, greenValue, blueValue);
    resetFlag = false; 
  }
}

void resetISR() {
  
  unsigned long currentInterruptTime = millis();
  if ((currentInterruptTime - lastInterruptTime) > debounceDelay) {
    resetFlag = true;
  }
  lastInterruptTime = currentInterruptTime;
}


void setLED(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

*/
