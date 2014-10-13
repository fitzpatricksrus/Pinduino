/*
 * OutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "OutputPins.h"


bool OutputPins::operator[](byte pinNdx) const {
	return getPin(pinNdx);
}

void OutputPins::setPins(bool* values) {
	for (int i = getPinCount() - 1; i >= 0; i--) {
		setPin(i, values[i]);
	}
}

void OutputPins::setAllPins(bool value) {
	for (int i = getPinCount() - 1; i >= 0; i--) {
		setPin(i, value);
	}
}

bool OutputPins::getAutoLatch() const {
	return autoLatch;
}

void OutputPins::setAutoLatch(bool latchOnEveryChange) {
	autoLatch = latchOnEveryChange;
}

void OutputPins::debug() {
	debug("", "");
}

void OutputPins::debug(const char* prefix, const char* postfix) {
	String s(prefix);
	s = s + "[";
	for (int i = 0; i < getPinCount(); i++) {
		s = s + getPin(i) + ", ";
	}
	s = s + "]" + postfix;
	Serial.print(s);
}
