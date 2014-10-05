/*
 * OutputPins.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */
#include "OutputPins.h"

#include "Arduino.h"

OutputPins::OutputPins(int pinCountIn, int pinsIn[])
: pinNumber(&pinsIn[0]), pinCount(pinCountIn)
{
	pinValue = new int[pinCountIn];
}

OutputPins::OutputPins(const OutputPins& source)
: pinNumber(source.pinNumber), pinCount(source.pinCount)
{
	pinValue = new int[pinCount];
}

OutputPins::~OutputPins() {
	delete[] pinValue;
}

OutputPins& OutputPins::operator=(const OutputPins& other) {
	if (this == &other) return *this;
	delete[] pinValue;
	pinNumber = other.pinNumber;
	pinCount = other.pinCount;
	pinValue = new int[pinCount];
	for (int i = 0; i < pinCount; i++) {
		pinValue[i] = other.pinValue[i];
	}
	return *this;
}

void OutputPins::initializePins(int value) {
    // this setup could easily be in the constructor if
    // we allocated the OutputPins in the setup() method,
    // but since we do it statically we need to wait
    // until setup() is called to initialize output pins.
    for (int i = 0; i < pinCount; i++) {
        pinMode(pinNumber[i], OUTPUT);
        analogWrite(pinNumber[i], value);
        pinValue[i] = value;
    }
}

void OutputPins::initializeDigitalPins(int value) {
    // this setup could easily be in the constructor if
    // we allocated the OutputPins in the setup() method,
    // but since we do it statically we need to wait
    // until setup() is called to initialize output pins.
    for (int i = 0; i < pinCount; i++) {
        pinMode(pinNumber[i], OUTPUT);
        digitalWrite(pinNumber[i], value);
        pinValue[i] = value;
    }
}

void OutputPins::setAnalogPin(int pinNdx, int value) {
    if (value == pinValue[pinNdx]) return;
	analogWrite(pinNumber[pinNdx], value);
    pinValue[pinNdx] = value;
}

void OutputPins::setAnalogPins(int* values) {
	for (int i = 0; i < pinCount; i++) {
		setAnalogPin(i, values[i]);
	}
}

void OutputPins::setAnalogPins(int value) {
	for (int i = 0; i < pinCount; i++) {
		setAnalogPin(i, value);
	}
}

void OutputPins::setDigitalPin(int pinNdx, int value) {
    if (value == pinValue[pinNdx]) return;
    digitalWrite(pinNumber[pinNdx], value);
    pinValue[pinNdx] = value;
}

void OutputPins::setDigitalPins(int* values) {
	for (int i = 0; i < pinCount; i++) {
		setDigitalPin(i, values[i]);
	}
}

void OutputPins::setDigitalPins(int value) {
	for (int i = 0; i < pinCount; i++) {
		setDigitalPin(i, value);
	}
}

void OutputPins::latch() {
	//doesn't do anything right now, but may later.
}

void OutputPins::debug() {
	debug("", "");
}
void OutputPins::debug(const char* prefix, const char* postfix) {
	String s(prefix);
	s = s + "[";
	for (int i = 0; i < pinCount; i++) {
		s = s + pinValue[i] + ", ";
	}
	s = s + "]" + postfix;
	Serial.print(s);
}
