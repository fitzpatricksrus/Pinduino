/*
 * SPIOutputPins.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: Dad
 */

#include "SPIOutputPins.h"
/*
    uint8_t valueCount;
    uint8_t* values;
    uint8_t SSPin;
    uint8_t SCKPin;
    uint8_t MOSIPin;
*/

SPIOutputPins::SPIOutputPins(uint8_t valueCountIn, int slaveSelectPinIn, int clockPinIn, int dataPinIn)
: valueCount(valueCountIn), SSPin(slaveSelectPinIn), SCKPin(clockPinIn), MOSIPin(dataPinIn)
{
	values = new uint8_t[valueCount];
}

SPIOutputPins::SPIOutputPins(const SPIOutputPins& source)
	: valueCount(source.valueCount), SSPin(source.SSPin), SCKPin(source.SCKPin), MOSIPin(source.MOSIPin)
{
	values = new uint8_t[valueCount];
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = source.values[i];
	}
}

SPIOutputPins::~SPIOutputPins() {
	delete[] values;
}

SPIOutputPins& SPIOutputPins::operator=(const SPIOutputPins& other) {
	if (this == &other) return *this;
	valueCount = other.valueCount;
	SSPin = other.SSPin;
	SCKPin = other.SCKPin;
	MOSIPin = other.MOSIPin;
	delete[] values;
	values = new uint8_t[valueCount];
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = other.values[i];
	}
	return *this;
}

void SPIOutputPins::initializePins(int value) {
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = value;
	}
}

void SPIOutputPins::initializePins(bool value) {
	initializePins((value) ? 255 : 0);
}

int SPIOutputPins::getPin(uint8_t pinNdx) const {
	return values[pinNdx];
}

int SPIOutputPins::operator[](uint8_t pinNdx) const {
	return values[pinNdx];
}

void SPIOutputPins::setPin(uint8_t pinNdx, int value) {
	values[pinNdx] = value;
}

void SPIOutputPins::setPins(int* valuesIn) {
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = valuesIn[i];
	}
}

void SPIOutputPins::setPins(int value) {
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = value;
	}
}

void SPIOutputPins::setPin(uint8_t pinNdx, bool value) {
	for (int i = valueCount -1; i >= 0; i--) {
		values[i] = value;
	}
}

void SPIOutputPins::setPins(bool* valuesIn) {
	for (int i = valueCount -1; i >= 0; i--) {
		setPin(i, valuesIn[i]);
	}
}

void SPIOutputPins::SPIOutputPins::setPins(bool value) {
	for (int i = valueCount -1; i >= 0; i--) {
		setPin(i, value);
	}
}

uint8_t SPIOutputPins::getPinCount() const {
	return valueCount;
}

void SPIOutputPins::latch() {

}

