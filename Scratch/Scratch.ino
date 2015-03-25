#include <Arduino.h>


void setup() {
	for (byte i = 2; i <= 13; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	Serial.begin(57600);
}

void loop() {
	for (int i = 0; i < 8; i++) {
		digitalWrite(2,  (i & 0x01) != 0);
		digitalWrite(3,  (i & 0x02) != 0);
		digitalWrite(4,  (i & 0x04) != 0);
		Serial.print((i & 0x01) != 0);
		Serial.print((i & 0x02) != 0);
		Serial.println((i & 0x04) != 0);
		delay(1000);
	}
}
