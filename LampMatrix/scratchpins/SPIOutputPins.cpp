/*
 * SPIOutputPins.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#include "SPIOutputPins.h"
#include "../SPI.h"

namespace pins {

SPIOutputPins::SPIOutputPins(byte valueCountIn, byte slaveSelectPin_ST_CPIn)
: valueCount(valueCountIn), encodedByteCount(0), encodedBytes(0), SSPin(slaveSelectPin_ST_CPIn)
{
	encodedByteCount = (valueCount+7) / 8;
	encodedBytes = new byte[encodedByteCount];
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		encodedBytes[i] = 0;
	}
}

SPIOutputPins::~SPIOutputPins() {
	delete [] encodedBytes;
}

void SPIOutputPins::initPins() const {
	SPI.begin();
	pinMode(SSPin, OUTPUT);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void SPIOutputPins::setPinPattern(PinPattern* pattern) {
	for (int i = 0; i < pattern->getPinCount(); i++) {
		byte bit = i % 8;
		byte bite = i / 8;
		encodedBytes[bite] = bitWrite(encodedBytes[bite], bit, (*pattern)[i]);
	}
}

void SPIOutputPins::latch() {
	digitalWrite(SSPin, LOW);
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		SPI.transfer(encodedBytes[i]);
	}
	digitalWrite(SSPin, HIGH);
}

SPIOutputPins& SPIOutputPins::slaveSelectPin(byte pinNumber) {
	SSPin = pinNumber;
	return *this;
}


byte SPIOutputPins::getSlavePin() const {
	return SSPin;
}

} /* namespace pins */
