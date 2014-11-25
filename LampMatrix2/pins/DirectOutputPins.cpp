/*
 * DirectOutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "DirectOutputPins.h"
#include "Arduino.h"
#include <stddef.h>

namespace pins {

DirectOutputPins::DirectOutputPins(byte pinCountIn, byte* pinsIn)
: pinCount(pinCountIn), pinNumber(pinsIn), pattern(NULL)
{
}

DirectOutputPins::~DirectOutputPins() {
}

void DirectOutputPins::initPins() const {
	for (int i = pinCount - 1; i >= 0; i--) {
		pinMode(pinNumber[i], OUTPUT);
	}
}

void DirectOutputPins::setPinPattern(PinPattern* patternIn) {
	pattern = patternIn;
}

void DirectOutputPins::latch() {
	for (int i = 0; i < pinCount; i++) {
		digitalWrite(pinNumber[i], ((*pattern)[i] ? HIGH : LOW));
	}
}

} // namespace pins


