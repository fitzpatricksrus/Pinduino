/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

BAMOutputPins::BAMOutputPins(unsigned int dutyCycleIn, MaxAnalogValue maxValueIn, OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), maxValue(maxValueIn), dutyCycleMicros(dutyCycleIn)
{
	values = new int[pins->getPinCount()];
}

BAMOutputPins::~BAMOutputPins() {
	delete[] values;
}

byte BAMOutputPins::getPinCount() const {
	return pins->getPinCount();
}

byte BAMOutputPins::getPin(byte pinNdx) const {
	return values[pinNdx];
}

void BAMOutputPins::setPin(byte pinNdx, byte pinValue) {
	values[pinNdx] = pinValue;
}

int bitInCycle = 0;
int valueMask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
void timerDelay(int bitNumber) {
}

void BAMOutputPins::latch(unsigned long now) {
	// this routine isn't done yet.  It needs to be the BAM modulation calculations
	bitInCycle = (bitInCycle + 1) & 0x07;
	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		pins->setPin(i, (values[i] & valueMask[bitInCycle]) !=0);
	}
	timerDelay(bitInCycle);
}
