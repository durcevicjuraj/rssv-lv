// koristenje IIC adaptere

#include <LiquidCrystal_I2C.h>

// HC-SR04 pinovi
const int triggerPin = 3;  // digitalni izlaz za trigger
const int echoPin    = 4;  // digitalni ulaz za echo

// Inicijalizacija LCD-a preko I²C adaptera s adresom 0x27 (često korištena adresa)
LiquidCrystal_I2C lcd(0x27, 16, 2);

const unsigned long updateInterval = 200;  // ažuriranje svakih 200 ms
unsigned long lastUpdateTime = 0;

void setup() {
  lcd.init();          // Inicijalizacija LCD-a
  lcd.backlight();     // Uključivanje pozadinskog osvjetljenja

  // Postavljanje HC-SR04 pinova
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();

    // Slanje ultrazvučnog impulsa:
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Mjerenje trajanja odjek impulsa
    long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30 ms
    float distance = duration / 58.0;  // pretvaranje u cm

    // Ako je udaljenost veća od 80 cm, postavi na 0
    if (distance > 80) {
      distance = 0;
    }

    // Prikaz na LCD-u
    lcd.clear();

    // Prvi redak: numerički prikaz
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm");

    // Drugi redak: grafički prikaz pomoću crtica
    // Skaliranje: udaljenost u rasponu [0,80] → broj crtica [0,16]
    int numDashes = map(distance, 0, 80, 0, 16);
    lcd.setCursor(0, 1);
    for (int i = 0; i < numDashes; i++) {
      lcd.print("-");
    }
  }
}

// bez iic adaptera

/*
#include <LiquidCrystal.h>

// Inicijalizacija LCD-a za paralelno spajanje: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// HC-SR04 pinovi (odabrani tako da ne konflikta s LCD-om)
const int triggerPin = 7;  // digitalni izlaz
const int echoPin    = 8;  // digitalni ulaz

const unsigned long updateInterval = 200;  // ažuriranje svakih 200 ms
unsigned long lastUpdateTime = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  // Postavljanje pinova za HC-SR04
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();

    // Slanje impulsa za HC-SR04:
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Mjerenje trajanja signala (timeout 30 ms)
    long duration = pulseIn(echoPin, HIGH, 30000);
    float distance = duration / 58.0;  // pretvaranje mjerenja u cm

    // Udaljenost iznad 80 cm se prikazuje kao 0
    if (distance > 80) {
      distance = 0;
    }

    // Prikaz podataka na LCD-u
    lcd.clear();

    // Prvi redak: numerički prikaz
    lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print(" cm");

    // Drugi redak: grafički prikaz pomoću crtica
    int numDashes = map(distance, 0, 80, 0, 16);
    lcd.setCursor(0, 1);
    for (int i = 0; i < numDashes; i++) {
      lcd.print("-");
    }
  }
}

*/
