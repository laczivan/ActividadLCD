#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>

const int pinIR = 2;
const int pinBuzzer = 3;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección común, cambia si es necesario

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Menu Principal");
  lcd.setCursor(0, 1);
  lcd.print("CH:Tono CH+:Alerta");

  IrReceiver.begin(pinIR, ENABLE_LED_FEEDBACK);
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    uint8_t code = IrReceiver.decodedIRData.command;
    IrReceiver.resume();

    lcd.clear();
    switch (code) {
      case 0x45: // CH−
        lcd.setCursor(0, 0);
        lcd.print("Tono Musical");
        tone(pinBuzzer, 1000, 500); // 1000 Hz por 500 ms
        break;

      case 0x47: // CH+
        lcd.setCursor(0, 0);
        lcd.print("Alerta Sonora");
        for (int i = 0; i < 3; i++) {
          tone(pinBuzzer, 2000);
          delay(300);
          noTone(pinBuzzer);
          delay(200);
        }
        break;

      case 0x0C: // Botón 1
        lcd.setCursor(0, 0);
        lcd.print("Botón 1: tono agudo");
        tone(pinBuzzer, 3000, 300);
        break;

      case 0x18: // Botón 2
        lcd.setCursor(0, 0);
        lcd.print("Botón 2: tono grave");
        tone(pinBuzzer, 500, 300);
        break;

      default:
        lcd.setCursor(0, 0);
        lcd.print("Codigo: 0x");
        lcd.print(code, HEX);
        break;
    }

    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Menu Principal");
    lcd.setCursor(0, 1);
    lcd.print("CH:Tono CH+:Alerta");
  }
}