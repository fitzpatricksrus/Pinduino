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
