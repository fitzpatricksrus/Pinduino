#include <Arduino.h>



void setup() {
	pinMode(A4, OUTPUT);

	Serial.begin(9600);
}

void loop() {
	byte v = digitalRead(A4);
	digitalWrite(A4, v ? LOW : HIGH);
	Serial.println(v ? "HIGH" : "LOW");
	delay(1000);
}
