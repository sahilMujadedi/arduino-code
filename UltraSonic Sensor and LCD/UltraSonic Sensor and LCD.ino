#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int TRIG_PIN = 6;
const int ECHO_PIN = 5;



float filterArray[20];
float distance;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(4, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("distance");
}

void loop() {
  // put your main code here, to run repeatedly:

  for (int sample = 0; sample < 20; sample++) {
    filterArray[sample] = ultrasonicMeasure("in");
    delay(10);
  }
  for (int i = 0; i < 19; i++) {
    for (int j = i + 1; j < 20; j++) {
      if (filterArray[i] > filterArray[j]) {
        float swap = filterArray[i];
        filterArray[i] = filterArray[j];
        filterArray[j] = swap;
      }
    }
  }
  double sum = 0;
  for (int sample = 5; sample < 15; sample++) {
    sum += filterArray[sample];
  }

  distance = sum / 10;

  if (distance <= 30) {
    digitalWrite(4, HIGH);

  }

  lcd.setCursor(0, 1);
  lcd.print(String(distance) + " in");


}

float ultrasonicMeasure(String unit) {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  float distance_unit;
  if (unit == "in") {
    float duration_us = pulseIn(ECHO_PIN, HIGH);
    distance_unit = 0.00663 * duration_us;
  } else if (unit == "cm") {
    float duration_us = pulseIn(ECHO_PIN, HIGH);
    distance_unit = 0.00663 * duration_us;
  }

  return distance_unit;
}

