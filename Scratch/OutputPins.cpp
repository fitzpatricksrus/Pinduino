/*
 * OutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "OutputPins.h"

OutputPins::OutputPins()
: autoLatch(false)
{
}

OutputPins::~OutputPins()
{
}

bool OutputPins::operator[](byte pinNdx) const {
	return getPin(pinNdx);
}

bool OutputPins::getAutoLatch() const {
	return autoLatch;
}

void OutputPins::setAutoLatch(bool latchOnEveryChange) {
	autoLatch = latchOnEveryChange;
}


void OutputPins::setPins(bool* values) {
	for (int i = getPinCount() - 1; i >= 0; i--) {
		setPin(i, values[i]);
	}
}

void OutputPins::setAllPins(long value) {
	for (int i = 0; i < getPinCount(); i++) {
		setPin(i, value & 0x01);
		value = value >> 1;
	}
}
