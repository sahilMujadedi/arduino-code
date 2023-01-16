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

    for (int j = 0; j < 4; j++) {
      bitWrite(LSNibble, j, bitRead(outputByte, j));
    }
	}
  return outputByte;
}
