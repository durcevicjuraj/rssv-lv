#include <LiquidCrystal.h>
#include <LedControl.h>

// Postavke za LCD – povezani su pinovi: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Postavke za LED matricu s MAX7219 kontrolerom:
// Parametri: (dataPin, clkPin, csPin, broj uređaja)
// U ovom primjeru DIN = 13, CLK = A5, CS = A4
LedControl lc = LedControl(13, A5, A4, 1);

unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 200; // Obnova prikaza svakih 200ms ili duže

void setup() {
  // Inicijaliziramo LCD
  lcd.begin(16, 2);
  lcd.clear();
  
  // Inicijaliziramo LED matricu – budimo sigurni da je modul uključen
  lc.shutdown(0, false);   // Uključuje LED matricu
  lc.setIntensity(0, 8);   // Postavlja intenzitet (0 - 15)
  lc.clearDisplay(0);
}

void loop() {
  // Obnovu prikaza ograničavamo svakih updateInterval (200 ms)
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();
    
    // Čitanje analognih vrijednosti s četiri pina (A0 do A3)
    int analogValues[4];
    for (int i = 0; i < 4; i++) {
      analogValues[i] = analogRead(A0 + i);
    }
    
    // Ažuriranje LCD zaslona:  
    // Formatiramo LCD da na prvoj liniji ispiše podatke s A0 i A1, a na drugoj s A2 i A3
    lcd.setCursor(0, 0);
    lcd.print("A0:");
    lcd.print(analogValues[0]);
    lcd.print(" A1:");
    lcd.print(analogValues[1]);
    
    lcd.setCursor(0, 1);
    lcd.print("A2:");
    lcd.print(analogValues[2]);
    lcd.print(" A3:");
    lcd.print(analogValues[3]);
    
    // Ažuriranje LED matrice:
    // Za svaki analogni kanal postavljamo stupac (stupci 0-3)
    // Skaliramo analognu vrijednost (0-1023) na raspon 0 do 8 LED-ova.
    for (int i = 0; i < 4; i++) {
      int height = map(analogValues[i], 0, 1023, 0, 8);
      // Ako je height 0, nijedan LED se ne svijetli; inače, izračunavamo pattern
      byte colPattern = (height == 0) ? 0 : (0xFF << (8 - height));
      lc.setColumn(0, i, colPattern);
    }
    // Očistimo preostale stupce (4 do 7) kako bi prikaz bio čist
    for (int i = 4; i < 8; i++) {
      lc.setColumn(0, i, 0);
    }
  }
}
