#include <Arduino.h>
#include "SPI.h"
#include "SPIOutputPins.h"
#include "scheduler/Timer.h"
#include "BAMOutputPins.h"

#define MEGA
#ifdef MEGA
static const int ColSelect = 40;
static const int RowSelect = 53;
static const int SCKPin = 52;
static const int MOSIPin = 51;
#else
static const int ColSelect = 9;
static const int RowSelect = 10;
static const int SCKPin = 13;
static const int MOSIPin = 11;
#endif



SPIOutputPins rgbPins(24, RowSelect, SCKPin, MOSIPin);
scheduler::Timer& timer = scheduler::Timer::timer1;
BAMOutputPins colorPins(&timer, &rgbPins);


//The setup function is called once at startup of the sketch
void setup()
{
	pinMode(RowSelect, OUTPUT);
	pinMode(ColSelect, OUTPUT);
	pinMode(SCKPin, OUTPUT);
	pinMode(MOSIPin, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	Serial.begin(9600);
    SPI.begin();
    timer.init();
    rgbPins.initPins();
}


static unsigned long delayMillis = 0;
static unsigned long delayMicros = 1;

// The loop function is called in an endless loop
static void loop1()
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
			delay(delayMillis);
			delayMicroseconds(delayMicros);
		}
	}
}

static void loop2() {
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
			delay(delayMillis);
			delayMicroseconds(delayMicros);
		}
	}
}


static void loop3() {
	int r = analogRead(A0) >> 2;
	int g = analogRead(A1) >> 2;
	int b = analogRead(A2) >> 2;

	digitalWrite(ColSelect, LOW);
	SPI.transfer(-1);
	digitalWrite(ColSelect, HIGH);
	for (int color = 0; color < 3; color++) {
		for (int i = 0; i < 8; i++) {
		}
		digitalWrite(RowSelect, LOW);
		SPI.transfer(((color == 0) ? r : 0));
		SPI.transfer(((color == 1) ? g : 0));
		SPI.transfer(((color == 2) ? b : 0));
		digitalWrite(RowSelect, HIGH);
		delay(delayMillis);
		delayMicroseconds(delayMicros);
	}
}

void loop() {
	loop3();
}

