#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// variables to receive and parse data from pc
// pc should use the form <date, time, temperature> to use this program
const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];       // temporary array to use when parsing to not change original data

char date[15] = {0};
char time[8] = {0};
char temperature[4] = {0};
// keep previous copies of variable to check against new ones.
char oldDate[15] = {0};
char oldTime[8] = {0};
char oldTemperature[4] = {0};

bool newData = false;

//-----------------

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

//-----------------

void loop() {
  recvData();
  if (newData == true) {
    strcpy(tempChars, receivedChars); // copy received chars into temp to be parsed
    parseData();
    printToLCD();
    newData = false;
  }
}

//----------------- 

void recvData() {
  static bool recvInProg = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProg == true) {
      // start adding the chars to receivedChars
      if (rc != endMarker) {
        // keep adding until endMarker has been hit
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          // in case there were too many characters before end marker
          ndx = numChars - 1;
        }
      } else {
        // end marker has been hit,   set index back to 0, and set newData to true to begin parsing
        // terminate the string,
        receivedChars[ndx] = '\0';
        // no longer receiving,
        recvInProg = false;
        // set index back to 0
        ndx = 0;
        // set newData to true to begin parsing
        newData = true;
      }
    } else if (rc == startMarker) {
      // the start marker has been found and now start running the above code
      recvInProg = true;
    }
  }
}

//-----------------

void parseData() { // split received data into parts
  char* strtokIndx;

  strtokIndx = strtok(tempChars, ","); // gets the first part, the date
  strcpy(date, strtokIndx); // copies it into date variable

  strtokIndx = strtok(NULL, ","); // NULL gets the part after, the time
  strcpy(time, strtokIndx); // copies it into time variable.

  strtokIndx = strtok(NULL, ",");
  strcpy(temperature, strtokIndx);
}

//-----------------

void printToLCD() { 
  lcd.setCursor(0,0);
  lcd.print(date);

  lcd.print(time);

  lcd.print(temperature);

}
