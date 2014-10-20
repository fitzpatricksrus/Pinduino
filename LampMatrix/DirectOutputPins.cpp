/*
 * DirectOutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "DirectOutputPins.h"

#include "Arduino.h"
#include "Tests/Debug.h"

DirectOutputPins::DirectOutputPins(byte pinCountIn, byte* pinsIn)
: pinNumber(pinsIn), pinCount(pinCountIn)
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
		pinValue[i] = false;
	}
}

void DirectOutputPins::setPin(byte pinNdx, bool value) {
    pinValue[pinNdx] = value;
    if (getAutoLatch()) {
		digitalWrite(pinNumber[pinNdx], value ? HIGH : LOW);
    }
}

void DirectOutputPins::latch() {
	for (int i = 0; i < pinCount; i++) {
		digitalWrite(pinNumber[i], pinValue[i] ? HIGH : LOW);
	}
}

byte DirectOutputPins::getPinCount() const {
    return pinCount;
}

bool DirectOutputPins::getPin(byte pinNdx) const {
	return pinValue[pinNdx];
}


