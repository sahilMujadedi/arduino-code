byte input = 14;

void setup() {
	Serial.begin(9600);
}

void loop() {
	BCDAlgo(input);
	delay(5000);
	input ++;
}
void BCDAlgo(byte inputByte) {
	byte LSNibble = 0;
	byte outputByte = 0;
	for (int i = 0; i < 8; i++) {
		if (LSNibble >= 5) {
			outputByte += 3;
		}
		outputByte = outputByte << 1;
		outputByte += bitRead(inputByte, 7 - i);
		LSNibble = (outputByte << 4) >> 4;
	}
	Serial.println(outputByte);
}
