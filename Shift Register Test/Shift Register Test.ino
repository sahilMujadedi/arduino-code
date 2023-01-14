const int LATCH_PIN = 11;
const int CLOCK_PIN = 9;
const int DATA_PIN = 12;

const int POTENTIAL_PIN = A0;

byte leds = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  leds=B11111100;
  updateShiftRegister();
  
  delay(200);
}

void updateShiftRegister() {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, leds);
  digitalWrite(LATCH_PIN, HIGH);
}