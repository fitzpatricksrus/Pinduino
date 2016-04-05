/*
 * RGBTest3.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: Dad
 */

#include "RGBTest3.h"

#include <Arduino.h>
#include <DueTimer.h>
#include "BitVector.h"

static const int COLUMN_SIZE = 8;

static int pins[] = { 22,23,24,25, 26,27,28,29, 34,35,36,37, 38,39,40,41 };
enum {
	DATA0,
	DATA1,
	DATA2,
	DATA3,
	DATA4,
	DATA5,
	DATA6,
	DATA7,
	CONTROL_ROWS, //CONTROL0,
	CONTROL_COLUMNS, //CONTROL1,
	CONTROL2,
	CONTROL3,
	CONTROL4,
	CONTROL5,
	CONTROL6,
	CONTROL7,
} Signal;

static inline void pinLow(int pin) {
    digitalWrite(pin, LOW);
}

static inline void pinHigh(int pin) {
    digitalWrite(pin, HIGH);
}

static inline void pinOn(int pin) {
    pinHigh(pin);
}

static inline void pinOff(int pin) {
    pinLow(pin);
}

static inline void on(int pin) {
    pinOn(pins[pin]);
}

static inline void off(int pin) {
    pinOff(pins[pin]);
}

static inline void signal(int ndx) {
    pinOn(pins[ndx]);
    pinOff(pins[ndx]);
}

RGBTest3::RGBTest3(byte* dataIn, int dataCountIn, int columnCountIn)
: position(0), dataCount(dataCountIn), data(dataIn), columnCount(columnCountIn)
{
}

RGBTest3::~RGBTest3() {

}

void RGBTest3::writeData(byte values) {
	BitVector v(values);
	for (int i = 0; i < v.size(); i++) {
		if (v[i]) {
			on(i);
		} else {
			off(i);
		}
	}
}

void RGBTest3::refreshOneComlumn(int col, byte value) {
	// turn off all columns
	writeData(0);
	signal(CONTROL_COLUMNS);

	// write rows
	writeData(value);
	signal(CONTROL_ROWS);

	// select the proper column
	writeData(1 << col);
	signal(CONTROL_COLUMNS);
}


void RGBTest3::refreshOneComlumn() {
	refreshOneComlumn(position % columnCount, data[position]);
	position = (position+1) % dataCount;
}
