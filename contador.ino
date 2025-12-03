#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección típica de LCD I2C 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin donde llega la señal del op-amp / botón de conteo
const int sensorPin = 13;

// Botón de reset (2 pines)
const int resetPin = 12;

int contador = 0;
int vueltas = 0;

bool estadoAnterior = LOW;

void setup() {
  pinMode(sensorPin, INPUT);        
  pinMode(resetPin, INPUT_PULLUP);    

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Contador: 0");
  lcd.setCursor(0, 1);
  lcd.print("Vueltas: 0");
}

void loop() {

  // ------------------ (RESET) ------------------
  if (digitalRead(resetPin) == LOW) {   // LOW = presionado
    contador = 0;
    vueltas = 0;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contador: 0");
    lcd.setCursor(0, 1);
    lcd.print("Vueltas: 0");

    delay(300); // Evita rebotes del botón
  }

  // ------------------ LECTURA DEL BOTÓN DE 4 PINES ------------------
  bool estado = digitalRead(sensorPin);

  // Detectar flanco ascendente: LOW → HIGH
  if (estado == HIGH && estadoAnterior == LOW) {

    contador++;

    if (contador % 15 == 0) {
      vueltas++;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contador: ");
    lcd.print(contador);

    lcd.setCursor(0, 1);
    lcd.print("Vueltas: ");
    lcd.print(vueltas);

    delay(200);
  }

  estadoAnterior = estado;
}
