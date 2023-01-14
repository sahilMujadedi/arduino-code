const int RED_LED = 5;
const int GREEN_LED = 6;
const int BLUE_LED = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}
// 120, 0, 255
void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(RED_LED, 255);
  analogWrite(GREEN_LED, 0);
  analogWrite(BLUE_LED, 255);
}
