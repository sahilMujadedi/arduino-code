#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String text;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    text = Serial.readStringUntil('\n');
    text.trim();
    lcd.print(text);
  }
  delay(1000);
}