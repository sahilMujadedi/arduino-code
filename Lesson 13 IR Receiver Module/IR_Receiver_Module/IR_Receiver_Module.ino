//www.elegoo.com
//2016.12.9

#include "IRremote.h"
const int num1[2] = { 5, 8 };
const int num2[5] = { 2, 4, 5, 6, 7 };
const int num3[5] = { 2, 4, 5, 7, 8 };
const int num4[4] = { 2, 3, 5, 8 };
const int num5[5] = { 2, 3, 4, 7, 8 };
const int num6[6] = { 2, 3, 4, 6, 7, 8 };
const int num7[4] = { 3, 4, 5, 8 };
const int num8[7] = { 2, 3, 4, 5, 6, 7, 8 };
const int num9[6] = { 2, 3, 4, 5, 7, 8 };
const int num0[6] = { 3, 4, 5, 6, 7, 8 };
const int error[5] = {2,3,4,6,7};

int receiver = 9; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFF6897: setNumber(0);    break;
  case 0xFF30CF: setNumber(1);    break;
  case 0xFF18E7: setNumber(2);    break;
  case 0xFF7A85: setNumber(3);    break;
  case 0xFF10EF: setNumber(4);    break;
  case 0xFF38C7: setNumber(5);    break;
  case 0xFF5AA5: setNumber(6);    break;
  case 0xFF42BD: setNumber(7);    break;
  case 0xFF4AB5: setNumber(8);    break;
  case 0xFF52AD: setNumber(9);    break;

  default: 
    setNumber(10);
  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

void setNumber(int n) {
  switch (n) {
    case 0:
      quickWrite(num0, 6);
      break;
    case 1:
      quickWrite(num1, 2);
      break;
    case 2:
      quickWrite(num2, 5);
      break;
    case 3:
      quickWrite(num3, 5);
      break;
    case 4:
      quickWrite(num4, 4);
      break;
    case 5:
      quickWrite(num5, 5);
      break;
    case 6:
      quickWrite(num6, 6);
      break;
    case 7:
      quickWrite(num7, 4);
      break;
    case 8:
      quickWrite(num8, 7);
      break;
    case 9:
      quickWrite(num9, 6);
      break;
    default:
      quickWrite(error, 5);
      break;
  }
}
void quickWrite(int arr[], int arrlen) {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  for (int i = 0; i < arrlen; i++) {
    digitalWrite(arr[i], HIGH);
  }
}
