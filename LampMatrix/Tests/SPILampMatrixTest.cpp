/*
 * SPILampMatrixTest.cpp
 *
 *  Created on: Oct 13, 2014
 *      Author: Dad
 */

#include "SPILampMatrixTest.h"
#include "../SPI.h"
#include "../SPIOutputPins.h"

namespace Tests {

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

SPILampMatrixTest SPILampMatrixTest::TEST;

SPILampMatrixTest::SPILampMatrixTest() {

}

SPILampMatrixTest::~SPILampMatrixTest() {
}

#define LOOP2

static long loopDelayMillis = 50;
static long loopDelayMicros = 1;

static SPIOutputPins rows = SPIOutputPins(24).slaveSelectPin(RowSelect);
static SPIOutputPins cols = SPIOutputPins(8).slaveSelectPin(ColSelect);


void SPILampMatrixTest::setup() {
	Serial.begin(9600);
	pinMode(RowSelect, OUTPUT);
	pinMode(ColSelect, OUTPUT);
	pinMode(SCKPin, OUTPUT);
	pinMode(MOSIPin, OUTPUT);
    SPI.begin();
}

unsigned long values[] = {
		1L    , 1L<<1,1L<<2 ,1L<<3 ,1L<<4 ,1L<<5 ,1L<<6 ,1L<<7,
		1L<<8 , 1L<<9,1L<<10,1L<<11,1L<<12,1L<<13,1L<<14,1L<<15,
		1L<<16,1L<<17,1L<<18,1L<<19,1L<<20,1L<<21,1L<<22,1L<<23,
};

#ifdef LOOP1
void SPILampMatrixTest::loop()
{
	for (byte col = 0; col < cols.getPinCount(); col++) {
		cols.setAllPins(values[col]);
		cols.latch();
		for (byte row = 0; row < rows.getPinCount(); row++) {
			rows.setAllPins(values[row]);
			rows.latch();
			delayMicroseconds(loopDelayMicros);
			delay(loopDelayMillis);
		}
	}
}
#endif

#ifdef LOOP2
void SPILampMatrixTest::loop()
{
	for (long row = 0; row < rows.getPinCount(); row++) {
		rows.setAllPins(values[row]);
		rows.latch();
		for (int col = 0; col < cols.getPinCount(); col++) {
			cols.setAllPins(values[col]);
			cols.latch();
			delayMicroseconds(loopDelayMicros);
			delay(loopDelayMillis);
		}
	}
}
#endif

#ifdef LOOP3
void SPILampMatrixTest::loop()
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
			delayMicroseconds(loopDelay);

		}
	}
}
#endif

#ifdef LOOP4
void SPILampMatrixTest::loop() {
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
			delayMicroseconds(loopDelay);
		}
	}
}
#endif

} /* namespace Tests */
