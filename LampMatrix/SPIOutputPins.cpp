/*
 * SPIOutputPins.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: Dad
 */

#include "SPIOutputPins.h"

#include "SPI.h"

/*
    uint8_t valueCount;
    uint8_t* values;
    uint8_t SSPin;
    uint8_t SCKPin;
    uint8_t MOSIPin;
*/

SPIOutputPins::SPIOutputPins(byte valueCountIn, byte slaveSelectPinIn, byte clockPinIn, byte dataPinIn)
: valueCount(valueCountIn), encodedByteCount(0), SSPin(slaveSelectPinIn), SCKPin(clockPinIn), MOSIPin(dataPinIn)
{
	encodedByteCount = (valueCount+7) / 8;
	encodedBytes = new byte[encodedByteCount];
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		encodedBytes[i] = 0;
	}
}

SPIOutputPins::SPIOutputPins(const SPIOutputPins& source)
	: valueCount(source.valueCount), encodedByteCount(source.encodedByteCount),
	  SSPin(source.SSPin), SCKPin(source.SCKPin), MOSIPin(source.MOSIPin)
{
	encodedBytes = new byte[encodedByteCount];
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		encodedBytes[i] = 0;
	}
}

SPIOutputPins::~SPIOutputPins() {
	delete[] encodedBytes;
}

SPIOutputPins& SPIOutputPins::operator=(const SPIOutputPins& other) {
	if (this == &other) return *this;
	valueCount = other.valueCount;
	SSPin = other.SSPin;
	SCKPin = other.SCKPin;
	MOSIPin = other.MOSIPin;
	delete[] encodedBytes;
	encodedByteCount = other.encodedByteCount;
	encodedBytes = new byte[encodedByteCount];
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		encodedBytes[i] = other.encodedBytes[i];
	}
	return *this;
}

static const byte masks[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
static const byte notmasks[] = { 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF, 0x7F };

//#define fastBitRead(value, bit) (value & masks[bit])
//#define fastBitSet(value, bit) (value | masks[bit])
//#define fastBitClear(value, bit) (value & notmasks[bit])
//#define fastBitWrite(value, bit, bitvalue) (bitvalue ? fastBitSet(value, bit) : fastBitClear(value, bit))

static byte fastBitRead(byte value, byte bit) {
	return value & masks[bit];
}

static byte fastBitSet(byte value, byte bit) {
	return value | masks[bit];
}

static byte fastBitClear(byte value, byte bit) {
	return value & notmasks[bit];
}

static byte fastBitWrite(byte value, byte bit, byte bitvalue) {
	if (bitvalue) {
		return fastBitSet(value, bit);
	} else {
		return fastBitClear(value, bit);
	}
}

void SPIOutputPins::initPins() const {
	SPI.begin();
}

bool SPIOutputPins::getPin(byte pinNdx) const {
	byte bit = pinNdx % 8;
	byte bite = pinNdx / 8;
	return fastBitRead(encodedBytes[bite], bit) != 0;
}

void SPIOutputPins::setPin(byte pinNdx, bool value) {
	byte bit = pinNdx % 8;
	byte bite = pinNdx / 8;
	encodedBytes[bite] = fastBitWrite(encodedBytes[bite], bit, value);
	if (getAutoLatch()) {
		latch();
	}
}

byte SPIOutputPins::getPinCount() const {
	return valueCount;
}

void SPIOutputPins::latch() {
	Serial.println(">latch");
	digitalWrite(SSPin, LOW);
	delay(1);
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		Serial.print("  encodedBytes: ");
		Serial.println(encodedBytes[i]);
		SPI.transfer(encodedBytes[i]);
		delay(1);
	}
	digitalWrite(SSPin, HIGH);
	delay(1);
	Serial.println("<latch");
}

SPIOutputPins& SPIOutputPins::slaveSelectPin(byte pinNumber) {
	SSPin = pinNumber;
	return *this;
}

SPIOutputPins& SPIOutputPins::clockPin(byte pinNumber) {
	SCKPin = pinNumber;
	return *this;
}

SPIOutputPins& SPIOutputPins::dataPin(byte pinNumber) {
	MOSIPin = pinNumber;
	return *this;
}

