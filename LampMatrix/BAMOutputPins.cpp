/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

static const byte valueMask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

BAMOutputPins::BAMOutputPins(unsigned int dutyCycleIn, OutputPins* pinsIn)
: AnalogOutputPins(), pins(pinsIn), values(0), dutyCycleMicros(), bitInCycle(0)
{
	values = new byte[pins->getPinCount()];
	unsigned int quantum = dutyCycleIn / 256;
	for (int i = 7; i >= 0; i--) {
		dutyCycleMicros[i] = quantum * valueMask[i];
	}
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

void BAMOutputPins::latch() {
	bitInCycle = (bitInCycle + 1) & 0x07;
	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		pins->setPin(i, (values[i] & valueMask[bitInCycle]) !=0);
	}
	delay(dutyCycleMicros[bitInCycle]);
}
