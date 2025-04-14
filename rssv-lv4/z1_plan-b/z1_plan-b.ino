// sa IIC adapterom

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LedControl.h>

// Inicijalizacija LCD-a preko I²C adaptera (adresa 0x27, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Inicijalizacija LED matrice (MAX7219): parametri su (dataPin, clkPin, csPin, broj uređaja)
// U ovom primjeru DIN=13, CLK=A5, CS=A4 – prilagodite prema svojoj shemi.
LedControl lc = LedControl(13, A5, A4, 1);

const unsigned long updateInterval = 200;  // period ažuriranja prikaza (200 ms ili više)
unsigned long lastUpdateTime = 0;

void setup() {
  // Inicijalizacija LCD-a
  lcd.init();          
  lcd.backlight();     
  
  // Postavljanje LED matrice: uključivanje, postavljanje intenziteta i čišćenje prikaza
  lc.shutdown(0, false);   
  lc.setIntensity(0, 8);   
  lc.clearDisplay(0);
}

void loop() {
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();

    // Čitanje "šuma" s četiri analogna pina
    int analogValues[4];
    for (int i = 0; i < 4; i++) {
      analogValues[i] = analogRead(A0 + i);
    }

    // Ažuriranje LCD prikaza
    lcd.clear();
    
    // Prvi redak: ispis podataka s A0 i A1 u formatu "A0: y A1: y"
    lcd.setCursor(0, 0);
    lcd.print("A0:"); lcd.print(analogValues[0]);
    lcd.print(" A1:"); lcd.print(analogValues[1]);
    
    // Drugi redak: ispis podataka s A2 i A3
    lcd.setCursor(0, 1);
    lcd.print("A2:"); lcd.print(analogValues[2]);
    lcd.print(" A3:"); lcd.print(analogValues[3]);

    // Ažuriranje prikaza na LED matrici
    // Za svaki analogni kanal, skaliramo očitanu vrijednost (0–1023) na broj LED-ova u stupcu (0–8)
    for (int i = 0; i < 4; i++) {
      int height = map(analogValues[i], 0, 1023, 0, 8);
      // Generiramo pattern stupca: ako je height nula, nijedan LED ne svijetli; inače se pomakne 0xFF
      byte colPattern = (height == 0) ? 0 : (0xFF << (8 - height));
      lc.setColumn(0, i, colPattern);
    }
    // Čistimo stupce od 4 do 7 kako bi prikaz bio uredan
    for (int i = 4; i < 8; i++) {
      lc.setColumn(0, i, 0);
    }
  }
}


// bez

/*
#include <LiquidCrystal.h>
#include <LedControl.h>

// Inicijalizacija LCD-a za paralelno spajanje:
// Parametri: (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Inicijalizacija LED matrice s MAX7219 kontrolerom:
// Parametri: (dataPin, clkPin, csPin, broj uređaja)
// Ovdje DIN=13, CLK=A5, CS=A4 – prilagodite prema vlastitoj shemi.
LedControl lc = LedControl(13, A5, A4, 1);

const unsigned long updateInterval = 200;  // ažuriranje svakih 200 ms ili više
unsigned long lastUpdateTime = 0;

void setup() {
  // Inicijaliziramo LCD
  lcd.begin(16, 2);
  lcd.clear();

  // Inicijaliziramo LED matricu: uključivanje i osnovne postavke
  lc.shutdown(0, false);   
  lc.setIntensity(0, 8);   
  lc.clearDisplay(0);
}

void loop() {
  if (millis() - lastUpdateTime >= updateInterval) {
    lastUpdateTime = millis();

    // Čitanje analognih "šuma" s A0 do A3
    int analogValues[4];
    for (int i = 0; i < 4; i++) {
      analogValues[i] = analogRead(A0 + i);
    }

    // Ažuriranje LCD prikaza u numeričkom obliku
    lcd.clear();
    
    // Prvi redak: podaci s A0 i A1
    lcd.setCursor(0, 0);
    lcd.print("A0:"); lcd.print(analogValues[0]);
    lcd.print(" A1:"); lcd.print(analogValues[1]);
    
    // Drugi redak: podaci s A2 i A3
    lcd.setCursor(0, 1);
    lcd.print("A2:"); lcd.print(analogValues[2]);
    lcd.print(" A3:"); lcd.print(analogValues[3]);

    // Ažuriranje LED matrice: skaliramo vrijednost (0–1023) na broj LED-ova (0–8) po stupcu
    for (int i = 0; i < 4; i++) {
      int height = map(analogValues[i], 0, 1023, 0, 8);
      byte colPattern = (height == 0) ? 0 : (0xFF << (8 - height));
      lc.setColumn(0, i, colPattern);
    }
    // Čistimo stupce od 4 do 7
    for (int i = 4; i < 8; i++) {
      lc.setColumn(0, i, 0);
    }
  }
}

*/