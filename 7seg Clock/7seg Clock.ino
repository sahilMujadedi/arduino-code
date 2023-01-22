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

const byte digits[5] = {
  B10000000, // first digit
  B01000000, // second digit
  B00100000, // third digit
  B00010000, // fourth digit
  B00001000  // AM PM led
};

ShiftReg digitSelect = {2, 3, 4};
ShiftReg segSelect = {5, 6, 7};
const int hourPin = 8;
const int minutePin = 9;
const int alarmPin = 10;
const int alarmLedPin = 11;
const int pageSelectPin = 12;

const bool BTN_PRESSED = false;
bool buttonDebounceHour = false; // variable to prevent multiple button registers on hours
bool buttonDebounceMinute = false; // variable to prevent multiple button registers on minutes
bool buttonDebouncePage = false; // variable to prevent multiple button registers on pageSelectPin

int dpSwitch = 0; // controls decimal point -- 0 = off, 1 = on
const unsigned int secondDur = 1000; // milliseconds
unsigned long currentTime = millis();
int page = 1;
bool alarmGoing = false;
bool alarmSwitcher = false;

byte hours = 12;
byte minutes = 0;
byte seconds = 0;
byte alarmHours = 6;
byte alarmMinutes = 0;
bool alarmMeridiem = 0;
bool meridiem = 0; // 0 = am, 1 = pm

byte hoursBCD;
byte minutesBCD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(digitSelect.latchPin, OUTPUT);
  pinMode(digitSelect.clockPin, OUTPUT);
  pinMode(digitSelect.dataPin, OUTPUT);
  pinMode(segSelect.latchPin, OUTPUT);
  pinMode(segSelect.clockPin, OUTPUT);
  pinMode(segSelect.dataPin, OUTPUT);
  pinMode(alarmLedPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);

  pinMode(hourPin, INPUT_PULLUP);
  pinMode(minutePin, INPUT_PULLUP);
  pinMode(pageSelectPin, INPUT_PULLUP);

  currentTime = millis();
  hoursBCD = doubleDabble(hours);
  minutesBCD = doubleDabble(minutes);
}

void loop() {
  // put your main code here, to run repeatedly:
  // run every second
  if (millis() >= (currentTime) + (secondDur)) {
    dpSwitch = !dpSwitch;
    seconds ++;
    if (seconds > 59) {
      seconds = 0;
      minutes ++;
      if (minutes > 59) {
        minutes = 0;
        hours ++;
        if (hours == 12) {
          meridiem = !meridiem;
        }
        if (hours > 12) {
          hours = 1;
        }
      }
    }
    if (alarmGoing) {
      digitalWrite(alarmLedPin, alarmSwitcher);
      digitalWrite(alarmPin, alarmSwitcher);
      alarmSwitcher = !alarmSwitcher;
    } else {
      digitalWrite(alarmPin, LOW);
    }
    currentTime = millis();
  }
  if (alarmMinutes == minutes && alarmHours == hours) {
    alarmGoing = true;
  } else {
    alarmGoing = false;
  }

  if (page == 1) {
    // when hours button is pressed
    if (digitalRead(hourPin) == BTN_PRESSED && buttonDebounceHour == false) {
      hours ++;
      if (hours == 12) {
        meridiem = !meridiem;
      } 
      if (hours > 12) {
        hours = 1;
      }
      buttonDebounceHour = true;
    }
    if (digitalRead(hourPin) != BTN_PRESSED && buttonDebounceHour == true) {
      buttonDebounceHour = false;
    }

    // when minutes button is pressed
    if (digitalRead(minutePin) == BTN_PRESSED && buttonDebounceMinute == false) {
      minutes ++;
      if (minutes > 59) {
        minutes = 0;
        hours ++;
        if (hours == 12) {
          meridiem = !meridiem;
        }
        if (hours > 12) {
          hours = 1;
        }
      } 
      buttonDebounceMinute = true;
    }
    if (digitalRead(minutePin) != BTN_PRESSED && buttonDebounceMinute == true) {
      buttonDebounceMinute = false;
    }
    minutesBCD = doubleDabble(minutes);
    hoursBCD = doubleDabble(hours);
  } else if (page == 2) {
    digitalWrite(alarmLedPin, HIGH);
    // when hours button is pressed
    if (digitalRead(hourPin) == BTN_PRESSED && buttonDebounceHour == false) {
      alarmHours ++;
      if (alarmHours == 12) {
        alarmMeridiem = !alarmMeridiem;
      } 
      if (alarmHours > 12) {
        alarmHours = 1;
      }
      buttonDebounceHour = true;
    }
    if (digitalRead(hourPin) != BTN_PRESSED && buttonDebounceHour == true) {
      buttonDebounceHour = false;
    }

    // when minutes button is pressed
    if (digitalRead(minutePin) == BTN_PRESSED && buttonDebounceMinute == false) {
      alarmMinutes ++;
      if (alarmMinutes > 59) {
        alarmMinutes = 0;
        alarmHours ++;
        if (alarmHours == 12) {
          alarmMeridiem = !alarmMeridiem;
        }
        if (alarmHours > 12) {
          alarmHours = 1;
        }
      } 
      buttonDebounceMinute = true;
    }
    if (digitalRead(minutePin) != BTN_PRESSED && buttonDebounceMinute == true) {
      buttonDebounceMinute = false;
    }
    minutesBCD = doubleDabble(alarmMinutes);
    hoursBCD = doubleDabble(alarmHours);
  }
  if (digitalRead(pageSelectPin) == BTN_PRESSED && buttonDebouncePage == false) {
    page ++;
    if (page > 2) {
      digitalWrite(alarmLedPin, LOW);
      page = 1;
    }
    buttonDebouncePage = true;
  }
  if (digitalRead(pageSelectPin) != BTN_PRESSED && buttonDebouncePage == true) {
    buttonDebouncePage = false;
  }
  
  updateDisplay();
}

void updateDisplay() {
  segSelect.outputData(B00000000); // clear segments before setting another to avoid ghosting effect
  
  // hours display
  // do not show zero behind hour
  if (hours >= 10 && page == 1) {
    digitSelect.outputData(digits[0]);
    segSelect.outputData(nums[hoursBCD >> 4]);
    segSelect.outputData(B00000000);
  }
  if (alarmHours >= 10 && page == 2) {
    digitSelect.outputData(digits[0]);
    segSelect.outputData(nums[hoursBCD >> 4]);
    segSelect.outputData(B00000000);
  }

  digitSelect.outputData(digits[1]);
  segSelect.outputData(nums[hoursBCD & 0x0f] + dpSwitch);  // x & 0x0f gets the 4 least significant bits of x
  
  // minutes display
  segSelect.outputData(B00000000);

  digitSelect.outputData(digits[2]);
  segSelect.outputData(nums[minutesBCD >> 4]);

  segSelect.outputData(B00000000);

  digitSelect.outputData(digits[3]);
  segSelect.outputData(nums[minutesBCD & 0x0f]);

  if (meridiem == true && page == 1) {
    digitSelect.outputData(digits[4]);
  }
  if (alarmMeridiem == true && page == 2) {
    digitSelect.outputData(digits[4]);
  }
}


// algorithm which converts a double digit decimal value into two single digit decimal values.
// i.e. 35 -> 3, 5
byte doubleDabble(byte input) {
  byte LSNibble = 0;
  byte MSNibble = 0;
	byte BCDValue = 0;
  

	for (int i = 0; i < 8; i++) {
		if (LSNibble >= 5) {
			BCDValue += 3;
		}

		BCDValue = BCDValue << 1;
		BCDValue += bitRead(input, 7 - i);

    for (int j = 0; j < 4; j++) {
      bitWrite(LSNibble, j, bitRead(BCDValue, j));
    }
	}

  return BCDValue;
}
