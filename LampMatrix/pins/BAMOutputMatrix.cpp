/*
 * BAMOutputMatrix.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: Dad
 */

#include "BAMOutputMatrix.h"
#include <Binary.h>

static const byte mask[] = { 0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000 };
static byte valueMap[256];

BAMOutputMatrix::BAMOutputMatrix(scheduler::Timer* timerIn, OutputPins* pinsIn, byte columnCountIn)
: pins(pinsIn), values(0), columnCount(columnCountIn), bitInCycle(0), colInCycle(0), timer(timerIn)
{
	values = new byte*[columnCount];
	byte rowCount = pinsIn->getPinCount();
	for (byte col = 0; col < columnCount; col++) {
		values[col] = new byte[rowCount];
	}
}

BAMOutputMatrix::~BAMOutputMatrix() {
	for (byte col = 0; col < columnCount; col++) {
		delete[] values[col];
	}
	delete [] values;
}

byte BAMOutputMatrix::getRowCount() const {
	return pins->getPinCount();
}

byte BAMOutputMatrix::getColumnCount() const {
	return pins->getPinCount();
}

byte BAMOutputMatrix::getPin(byte col, byte row) const {
	return values[col][row];
}

void BAMOutputMatrix::setPin(byte col, byte row, byte pinValue) {
	values[col][row] = pinValue;
}

void BAMOutputMatrix::latch() {
	timer->addCallback(this);
}

void BAMOutputMatrix::setup() {
	//reset the timer
	bitInCycle = 0;
	colInCycle = 0;
	for (int i = 0; i < pins->getPinCount(); i++) {
		values[i] = 0;
		pins->setPin(i, 0);
	}
	for (int i = 0; i < 256; i++) {
		valueMap[i] = i;
		if (i > 128) {
    		valueMap[i] = map(i, 128, 256, 64, 256);
    	} else if (i > 16){
    		valueMap[i] = map(i, 16, 128, 4, 64);
    	} else {
    		valueMap[i] = map(i, 0, 16, 0, 4);
    	}
	}
}

void BAMOutputMatrix::loop() {
	bitInCycle += 1;
	if (bitInCycle > 0b00000111) {
		bitInCycle = 0;
		colInCycle += 1;
		if (colInCycle > columnCount) {
			colInCycle = 0;
		}
	}
    for (int i = 0; i < pins->getPinCount(); i++) {
    	byte value = values[colInCycle][i];
    	value = valueMap[value];
        bool isOn = ((value & mask[bitInCycle]) != 0);
    	pins->setPin(i, isOn);
    }
    pins->latch();
    unsigned long rval = mask[bitInCycle];
    timer->setTicks(rval << 1);
}
