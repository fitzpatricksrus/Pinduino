#include <Arduino.h>
#include "SPI.h"

static const int columnPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static const int SSPin = 10;
static const int SCKPin = 13;
static const int MOSIPin = 11;


//The setup function is called once at startup of the sketch
void setup()
{
	for (int i = 0; i < 8; i++) {
		pinMode(columnPins[i], OUTPUT);
		digitalWrite(columnPins[i], LOW);
	}
	Serial.begin(9600);
    SPI.begin();
}

// The loop function is called in an endless loop
void loop()
{
	Serial.println("Hello?");
	for (long i = 0; i < 24; i++) {
		long x = 1;
		for (int col = 0; col < 8; col++) {
			for (int c = 0; c < 8; c++) {
				digitalWrite(columnPins[c], (c == col) ? HIGH : LOW);
			}
			digitalWrite(SSPin, LOW);
			long x = 1L << i;

			SPI.transfer((x & 0x0000FF00L) >> 8);
			SPI.transfer((x & 0x000000FFL));
			SPI.transfer((x & 0x00FF0000L) >> 16);
			digitalWrite(SSPin, HIGH);
/*			Serial.print("Col: ");
			Serial.print(col);
			Serial.print("  Row: ");
			Serial.print(i);
			Serial.print("  RGB(");
			Serial.print((x & 0x00FF0000) >> 16);
			Serial.print(",");
			Serial.print((x & 0x0000FF00) >> 8);
			Serial.print(",");
			Serial.print((x & 0x000000FF));
			Serial.println(")");*/
//			delay(1);

		}
	}
}
