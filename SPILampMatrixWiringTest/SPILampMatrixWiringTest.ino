#include <Arduino.h>
#include "SPI.h"

static const int ColSelect = 9;
static const int RowSelect = 10;
static const int SCKPin = 13;
static const int MOSIPin = 11;


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(RowSelect, OUTPUT);
	pinMode(ColSelect, OUTPUT);
	pinMode(SCKPin, OUTPUT);
	pinMode(MOSIPin, OUTPUT);
	Serial.begin(9600);
    SPI.begin();
}


void loop() {
	loop1();
}

// The loop function is called in an endless loop
void loop1()
{
	for (long i = 0; i < 24; i++) {
		for (int col = 0; col < 8; col++) {
			digitalWrite(ColSelect, LOW);
			SPI.transfer(1 << col);
			digitalWrite(ColSelect, HIGH);
			digitalWrite(RowSelect, LOW);
			long x = 1L << i;
			SPI.transfer((x & 0x0000FF00L) >> 8);
			SPI.transfer((x & 0x000000FFL));
			SPI.transfer((x & 0x00FF0000L) >> 16);
			digitalWrite(RowSelect, HIGH);
		//	delay(20);
			delayMicroseconds(20);

		}
	}
}
void loop2() {
	for (byte col = 0; col < 8; col++) {
		for (byte row = 0; row < 24; row++) {
			digitalWrite(ColSelect, LOW);
			SPI.transfer(1 << col);
			digitalWrite(ColSelect, HIGH);
			digitalWrite(RowSelect, LOW);
			long x = 1L << row;
			SPI.transfer((x & 0x0000FF00L) >> 8);
			SPI.transfer((x & 0x000000FFL));
			SPI.transfer((x & 0x00FF0000L) >> 16);
			digitalWrite(RowSelect, HIGH);
			delay(50);
		}
	}
}
