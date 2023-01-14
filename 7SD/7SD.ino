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

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 10; i++) {
    setNumber(i);
    delay(250);
  }
}

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
