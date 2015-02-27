#include <Arduino.h>

void setData(byte value) {
	for (byte i = 0; i < 8; i++) {
		if (value == i) {
			digitalWrite(4+i, LOW);
		} else {
			digitalWrite(4+i, HIGH);
		}
	}
}

void toggle(byte pin) {
	digitalWrite(pin, LOW);
	for (int i = 0; i < 200; i++) {
		i << i;
	}
	digitalWrite(pin, HIGH);
}

void setup() {
	for (byte i = 2; i <= 13; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
	}
	toggle(4);
	toggle(5);
	toggle(2);
	toggle(3);
}

void loop() {
/*	toggle(2);
	delay(1);
	toggle(3);
	delay(1);
	toggle(4);
	delay(1);
	toggle(5);
	delay(1);
	setData(0); toggle(3);delay(5);
	setData(0); toggle(2);delay(5);
	delay(100);

	setData(0); toggle(3);delay(5);
	setData(1); toggle(2);delay(5);
	delay(100);

	setData(1); toggle(3);delay(5);
	setData(0); toggle(2);delay(5);
	delay(100);

	setData(1); toggle(3);delay(5);
	setData(1); toggle(2);delay(5);
	delay(100); */


	for (byte col = 0; col < 8; col++) {
		setData(col);
		toggle(3);delayMicroseconds(15);
		for (byte row = 0; row < 8; row++) {
			setData(row);
			toggle(2);
			delayMicroseconds(15);
		}
	}

}
