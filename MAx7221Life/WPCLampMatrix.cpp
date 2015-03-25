/*
 * WPCLampMatrix.cpp
 *
 *  Created on: Jan 25, 2015
 *      Author: Dad
 */

#include "WPCLampMatrix.h"

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

void WPCLampMatrix::setColumn(byte column, byte values) {
	if (!isInited) {
		pinMode(colSelectPin, OUTPUT);
		pinMode(rowSelectPin, OUTPUT);
		for (byte i = 0; i < 8; i++) {
			pinMode(firstDataPin + i, OUTPUT);
		}
		isInited = true;
	}

	digitalWrite(colSelectPin, LOW);
	writeDataPins(~(1 << column));
	digitalWrite(colSelectPin, HIGH);

	digitalWrite(rowSelectPin, LOW);
	writeDataPins(~values);
	digitalWrite(rowSelectPin, HIGH);
}

void WPCLampMatrix::writeDataPins(byte value) {
	for (byte i = 0; i < 8; i++) {
		digitalWrite(firstDataPin + i, value & 1);
		value = value >> 1;
	}
}

