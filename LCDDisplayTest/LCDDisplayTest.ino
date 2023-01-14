#include <LiquidCrystal.h>

const bool BTN_PRESSED = false;

const int clickPin = 2;
const int autoPin = 3;
const int ledPin = 13;
const int analogStick = A0;

int page = 1;
int topPage = 5;

unsigned long money = 0;
int clickValue = 1;

int totalWorkers = 0;
int workerValue = 1;
int workerCap = 3;
unsigned int hireCost = 10;
unsigned int workerCapCost = 300;
unsigned int workerValueCost = 200;
unsigned int clickValueCost = 250;


const int intervalTime = 1000;
unsigned long currentTime = millis();

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(autoPin, INPUT_PULLUP);
  pinMode(clickPin, INPUT_PULLUP);
  Serial.begin(9600);
  currentTime = millis();
  setupScreen();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (millis() >= (currentTime) + (intervalTime)) {
    money += (totalWorkers)*(workerValue);
    currentTime = millis();
  }
  if (analogRead(analogStick) <= 124) {
    // move right
    if (page == topPage) {
      page = 1;
    } else {
      page += 1;
    }
    setupScreen();
    while (analogRead(analogStick) <= 124) {
      // do nothing.
    }
  } else if (analogRead(analogStick) >= 900) {
    // move left
    if (page == 1) {
      page = topPage;
    } else {
      page -= 1;
    }
    setupScreen();
    while (analogRead(analogStick) >= 900) {
      // do nothing.
    }
  }

  if (page == 1) {
    
    lcd.setCursor(0, 1);
    lcd.print(String(money));
    
    lcd.setCursor(11, 1);
    lcd.print("$" + String(totalWorkers*workerValue));

    canClick();
    canHire();
    
    if (money >= hireCost && totalWorkers < workerCap) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  } else if (page == 2) {

    lcd.setCursor(0, 1);
    lcd.print("$" + String(hireCost));

    lcd.setCursor(10, 1);
    lcd.print(String(totalWorkers) + "/" + String(workerCap));

    canHire();
    canClick();

    if (money >= hireCost && totalWorkers < workerCap) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  } else if (page == 3) {
    lcd.setCursor(0, 1);
    lcd.print("$" + String(workerCapCost));
    if (digitalRead(autoPin) == BTN_PRESSED && money >= workerCapCost) {
      workerCap += 2;
      money -= workerCapCost;
      workerCapCost *= 3;
      while (digitalRead(autoPin) == BTN_PRESSED) {
        // do nothing.
      }
    }
    if (money >= workerCapCost) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    
  } else if (page == 4) {
    lcd.setCursor(0, 1);
    lcd.print("$" + String(workerValueCost));
    if (digitalRead(autoPin) == BTN_PRESSED && money >= workerValueCost) {
      workerValue += 1;
      money -= workerValueCost;
      workerValueCost *= 3;
      while (digitalRead(autoPin) == BTN_PRESSED) {
        // do nothing.
      }
    }
    if (money >= workerValueCost) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
    
  } else if (page == 5) {
    lcd.setCursor(0, 1);
    lcd.print("$" + String(clickValueCost));
    if (digitalRead(autoPin) == BTN_PRESSED && money >= clickValueCost) {
      clickValue += 5;
      money -= clickValueCost;
      clickValueCost *= 3;
      while (digitalRead(autoPin) == BTN_PRESSED) {
        // do nothing.
      }
    }
    if (money >= clickValueCost) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
  
}

void canHire() {
  if (digitalRead(autoPin) == BTN_PRESSED && money >= hireCost && totalWorkers < workerCap) {
    setupScreen();
    totalWorkers += 1;
    money -= hireCost;
    hireCost *= 2;
    while (digitalRead(autoPin) == BTN_PRESSED) {
      // do nothing to prevent auto clicks.
    }
  } 
}
void canClick() {
  if (digitalRead(clickPin) == BTN_PRESSED) {
    money += clickValue;
    while (digitalRead(clickPin) == BTN_PRESSED) {
      // do nothing to prevent auto clicks.
    }
  }
}

// used so that display can be erased when changed.
void setupScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  if (page == 1) {
    lcd.print("$");
    lcd.setCursor(10, 0);
    lcd.print("$/sec");
  } else if (page == 2) {
    lcd.print("Hire");
    lcd.setCursor(9, 0);
    lcd.print("Workers");
  } else if (page == 3) {
    lcd.print("Buy +2 WorkerCap");
  } else if (page == 4) {
    lcd.print("Buy +1 WorkerEff");
  } else if (page == 5) {
    lcd.print("Buy +5 ClickVal");
  }
}
