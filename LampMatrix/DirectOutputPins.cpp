/*
 * DirectOutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "DirectOutputPins.h"

#include "Arduino.h"

DirectOutputPins::DirectOutputPins(byte pinCountIn, byte pinsIn[])
: pinNumber(&pinsIn[0]), pinCount(pinCountIn)
{
	pinValue = new bool[pinCountIn];
}

DirectOutputPins::DirectOutputPins(const DirectOutputPins& source)
: pinNumber(source.pinNumber), pinCount(source.pinCount)
{
	pinValue = new bool[pinCount];
}

DirectOutputPins::~DirectOutputPins() {
	delete[] pinValue;
}

DirectOutputPins& DirectOutputPins::operator=(const DirectOutputPins& other) {
	if (this == &other) return *this;
	delete[] pinValue;
	pinNumber = other.pinNumber;
	pinCount = other.pinCount;
	pinValue = new bool[pinCount];
	for (int i = pinCount - 1; i >= 0; i--) {
		pinValue[i] = other.pinValue[i];
	}
	return *this;
}

void DirectOutputPins::initPins() const {
	for (int i = pinCount - 1; i >= 0; i--) {
		pinMode(pinNumber[i], OUTPUT);
	}
}

void DirectOutputPins::setPin(byte pinNdx, bool value) {
    pinValue[pinNdx] = value;
    if (getAutoLatch()) {
		digitalWrite(pinNumber[pinNdx], value ? HIGH : LOW);
    }
}

void DirectOutputPins::latch() {
	for (int i = pinCount - 1; i >= 0; i--) {
		digitalWrite(pinNumber[i], pinValue[i] ? HIGH : LOW);
	}
}
