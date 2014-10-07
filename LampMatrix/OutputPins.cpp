/*
 * OutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "OutputPins.h"

#include "Arduino.h"

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
