/*
 * WPCLampMatrix.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: Dad
 */

#include "WPCLampMatrix.h"

//#define _DEBUG_
#ifdef _DEBUG_
#include <Debug.h>
#endif

static long const lowDelay = 28;
static inline void delayJustATad() {
	delayMicroseconds(lowDelay);
}

/*
 * The WPC lamp matrix is driven by a row select pin, a column select pin, and
 * a shared 8 bit data bus.  To turn a set of rows on, 8 bits of data is put on the
 * data bus, low signifying that the row should be ENABLED.  The row select pin is then
 * toggled from low to high to latch the data.  The setup for the columns is the same.
 * data is put on the data bus, low signifying the column is on, and the rising transition
 * on the column select pin latches the data.  The columns have a single master output
 * control (OC) line that turns the enables the output of puts them into a high impedance state.
 * When OC is low, the output are high impedance.
 */
WPCLampMatrix::WPCLampMatrix(byte colSelectPinIn, byte rowSelectPinIn, byte firstDataPinIn)
: colSelectPin(colSelectPinIn), rowSelectPin(rowSelectPinIn), firstDataPin(firstDataPinIn), isInited(false)
{
}

WPCLampMatrix::~WPCLampMatrix() {
}

void WPCLampMatrix::init() {
	if (!isInited) {
		pinMode(colSelectPin, OUTPUT);
		digitalWrite(colSelectPin, HIGH);
		pinMode(rowSelectPin, OUTPUT);
		digitalWrite(rowSelectPin, HIGH);
		for (byte i = 0; i < 8; i++) {
			pinMode(firstDataPin + i, OUTPUT);
			digitalWrite(firstDataPin + i, HIGH);
		}
		isInited = true;
	}
//	pinMode(12, OUTPUT);
//	pinMode(13, OUTPUT);
}

inline void WPCLampMatrix::writeDataPins(byte value) {
	digitalWrite(firstDataPin + 0, (value & 0x01) != 0);
	digitalWrite(firstDataPin + 1, (value & 0x02) != 0);
	digitalWrite(firstDataPin + 2, (value & 0x04) != 0);
	digitalWrite(firstDataPin + 3, (value & 0x08) != 0);
	digitalWrite(firstDataPin + 4, (value & 0x10) != 0);
	digitalWrite(firstDataPin + 5, (value & 0x20) != 0);
	digitalWrite(firstDataPin + 6, (value & 0x40) != 0);
	digitalWrite(firstDataPin + 7, (value & 0x80) != 0);
}

#if 0
void WPCLampMatrix::setColumn(byte column, byte values) {
	setColumn(column);
	setRows(values);
}
#else
void WPCLampMatrix::setColumn(byte column, byte values) {
	writeDataPins(-1);	//turn off all columns
	digitalWrite(colSelectPin, LOW);
	delayJustATad();
	digitalWrite(colSelectPin, HIGH);
	delayJustATad();

	// write the row data
	writeDataPins(~values);
	digitalWrite(rowSelectPin, LOW);
	delayJustATad();
	digitalWrite(rowSelectPin, HIGH);
	delayJustATad();

	// turn the proper column on
	writeDataPins(~(1 << column));
	digitalWrite(colSelectPin, LOW);
	delayJustATad();
	digitalWrite(colSelectPin, HIGH);
	delayJustATad();
}
#endif

void WPCLampMatrix::setColumn(byte column) {
#ifdef _DEBUG_
	Serial << "COL ";
#endif
	writeDataPins(~(1 << column));
	digitalWrite(colSelectPin, LOW);
	delayJustATad();
	digitalWrite(colSelectPin, HIGH);
	delayJustATad();
}

void WPCLampMatrix::setRows(byte values) {
#ifdef _DEBUG_
	Serial << "    ROWs  ";
#endif
	writeDataPins(~values);
	digitalWrite(rowSelectPin, LOW);
	delayJustATad();
	digitalWrite(rowSelectPin, HIGH);
	delayJustATad();
#ifdef _DEBUG_
	Serial << endl;
#endif
}
