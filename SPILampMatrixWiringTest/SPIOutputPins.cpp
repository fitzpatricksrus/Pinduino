/*
 * SPIOutputPins.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: Dad
 */

#include "SPIOutputPins.h"

#include <Arduino.h>
#include <Binary.h>
#include "SPI.h"

/*
    uint8_t valueCount;
    uint8_t* values;
    uint8_t SSPin;
    uint8_t SCKPin;
    uint8_t MOSIPin;
*/

static const byte masks[] =    { B00000001,B00000010,B00000100,B00001000,B00010000,B00100000,B01000000,B10000000 };
static const byte notmasks[] = { B11111110,B11111101,B11111011,B11110111,B11101111,B11011111,B10111111,B01111111 };


#ifdef ARDUINO_AVR_UNO
inline void Macro_SetPinLow(byte pin)  {
	if ( (pin) < 8 ) {
		PORTD = PORTD & notmasks[pin];
	} else {
		PORTB = PORTB & notmasks[pin - 8];
	}
}

inline void Macro_SetPinHigh( byte pin ) {
	if ( (pin) < 8 ) {
		PORTD = PORTD | masks[pin];
	} else {
		PORTB = PORTB | masks[pin - 8];
	}
}

inline void Macro_SetPin(byte pin, bool state ) {
	if ( state  ) {
		Macro_SetPinHigh( (pin) );
	} else {
		Macro_SetPinLow( (pin) );
	}
}
#else
inline void Macro_SetPin(byte pin, bool state ) {
	digitalWrite(pin, state);
}
#endif


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

//#define fastBitRead(value, bit) (value & masks[bit])
//#define fastBitSet(value, bit) (value | masks[bit])
//#define fastBitClear(value, bit) (value & notmasks[bit])
//#define fastBitWrite(value, bit, bitvalue) (bitvalue ? fastBitSet(value, bit) : fastBitClear(value, bit))

static inline byte fastBitRead(byte value, byte bit) {
	return value & masks[bit];
}

static inline byte fastBitSet(byte value, byte bit) {
	return value | masks[bit];
}

static inline byte fastBitClear(byte value, byte bit) {
	return value & notmasks[bit];
}

static inline byte fastBitWrite(byte value, byte bit, byte bitvalue) {
	if (bitvalue) {
		return fastBitSet(value, bit);
	} else {
		return fastBitClear(value, bit);
	}
}

void SPIOutputPins::initPins() const {
	SPI.begin();
	pinMode(SSPin, OUTPUT);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
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

void SPIOutputPins::set32Pins(long value) {
	for (int i = 0; i < encodedByteCount; i++) {
		encodedBytes[i] = value & 0xFF;
		value = value >> 8;
	}
}

void SPIOutputPins::setAllPins(byte* value) {
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		encodedBytes[i] = value[i];
	}
}

byte SPIOutputPins::getPinCount() const {
	return valueCount;
}

void SPIOutputPins::latch() {
	Macro_SetPin(SSPin, LOW);
//	Serial.print("dev: "); Serial.print(SSPin); Serial.print(" ");
	for (int i = encodedByteCount - 1; i >= 0; i--) {
		SPI.transfer(encodedBytes[i]);
//		Serial.print(encodedBytes[i]);
//		Serial.print(" ");
	}
	Macro_SetPin(SSPin, HIGH);
//	Serial.println(" ");
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

byte SPIOutputPins::getSlavePin() const {
	return SSPin;
}
byte SPIOutputPins::getClockPin() const {
	return SCKPin;
}
byte SPIOutputPins::getDataPin() const {
	return MOSIPin;
}

