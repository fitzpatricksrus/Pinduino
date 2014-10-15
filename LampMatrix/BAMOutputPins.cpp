/*
 * BAMOutputPins.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "BAMOutputPins.h"

static const byte valueMask[] = { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };

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
	// TODO - this should use a timer or something
	for (int i = pins->getPinCount() - 1; i >= 0; i--) {
		pins->setPin(i, (values[i] & valueMask[bitInCycle]) !=0);
	}
	bitInCycle = (bitInCycle + 1) & 0x07;
}

