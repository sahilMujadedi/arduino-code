const int LATCH_PIN = 2;
const int CLOCK_PIN = 3;
const int DATA_PIN = 4;

const byte nums[10] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100100, // 7
  B11111110, // 8
  B11110110  // 9
};

void set7SegDisp(byte digit) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, nums[digit]);
  digitalWrite(LATCH_PIN, HIGH);
}


void setup() {
  // put your setup code here, to run once:
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 10; i++) {
    set7SegDisp(i);
    delay(300);
  }
  
  
}

