/*
 * AnalogOutputPin.cpp
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#include "AnalogOutputPins.h"

AnalogOutputPins::AnalogOutputPins() {
}

AnalogOutputPins::~AnalogOutputPins() {
}

byte AnalogOutputPins::operator[](byte pinNdx) const {
	return getPin(pinNdx);
}

void AnalogOutputPins::setPins(const byte* pinValues) {
	for (int i = getPinCount() - 1; i >=0; i--) {
		setPin(i, pinValues[i]);
	}
}
