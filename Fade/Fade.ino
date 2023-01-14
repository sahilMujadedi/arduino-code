const int led = 9;
int speed = 5;
int brightness = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);    
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(led, brightness);
  brightness = brightness + speed;
  if (brightness >= 255 || brightness <= 0) {
    speed = -speed;
  }
  delay(10);
}
