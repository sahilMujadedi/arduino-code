class ShiftReg {
  public:
    int latchPin;
    int clockPin;
    int dataPin;
    void outputData(byte data) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, data);
      digitalWrite(latchPin, HIGH);
    }
};

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

int dp = 1; // add to a nums value to output a decimal point.

const byte digitNum[4] = {
  B10000000, // first digit
  B01000000, // second digit
  B00100000, // third digit
  B00010000  // fourth digit
};

unsigned byte ones = B0000
unsigned byte tens = B0000

ShiftReg digitSelect = {2, 3, 4};
ShiftReg segSelect = {5, 6, 7};

int digitVal[4] = {1, 2, 1, 0};

bool dpSwitch = true;
const int intervalDur = 1000; // milliseconds
unsigned long currentTime = millis();

int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(digitSelect.latchPin, OUTPUT);
  pinMode(digitSelect.clockPin, OUTPUT);
  pinMode(digitSelect.dataPin, OUTPUT);
  pinMode(segSelect.latchPin, OUTPUT);
  pinMode(segSelect.clockPin, OUTPUT);
  pinMode(segSelect.dataPin, OUTPUT);
  currentTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  // run on an interval
  if (millis() >= (currentTime) + (intervalDur)) {
    dpSwitch = !dpSwitch;
    seconds ++;
    
    currentTime = millis();
  }
  if (seconds > 59) {
    minutes ++;
    if (minutes > 59) {
      hours ++;
      if (hours > 12) {
        hours = 1;
      }
    }
  }
  updateDisplay();

}

void updateDisplay() {
  // for (int i = 0; i < 4; i++) {
  //   segSelect.outputData(B00000000);
  //   digitSelect.outputData(digitNum[i]);
  //   if (digitNum[i] == digitNum[1] && dpSwitch) {
  //     segSelect.outputData(nums[digitVal[i]] + dp);
  //   } else {
  //     segSelect.outputData(nums[digitVal[i]]);
  //   }
    
  // }
}

void doubleDabble(byte input) {
  
}
