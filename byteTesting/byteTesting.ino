void setup() {
	Serial.begin(9600);
  Serial.println(BCDAlgo(57));
}

void loop() {

}
byte BCDAlgo(byte inputByte) {
	byte LSNibble = 0;
	byte outputByte = 0;

	for (int i = 0; i < 8; i++) {
		if (LSNibble >= 5) {
			outputByte += 3;
		}

		outputByte = outputByte << 1;
		outputByte += bitRead(inputByte, 7 - i);

    LSNibble = outputByte & 0x0f;
	}
  return outputByte;
}
