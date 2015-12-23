/*
 * Max7221.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: Dad
 */

#include "Max7221.h"

#include <Arduino.h>
#include <SPI.h>

class MAX7221_COMMAND {
public:
	enum {
		noop =      0b00000000,
		digit0 =    0b00000001,
		digit1 =    0b00000010,
		digit2 =    0b00000011,
		digit3 =    0b00000100,
		digit4 =    0b00000101,
		digit5 =    0b00000110,
		digit6 =    0b00000111,
		digit7 =    0b00001000,
		decode =    0b00001001,
		intensity = 0b00001010,
		scanLimit = 0b00001011,
		enable =    0b00001100,
		unused1 =   0b00001101,
		unused2 =   0b00001110,
		test =      0b00001111
	};
};

Max7221::Max7221(byte selectPinIn)
: selectPin(selectPinIn)
{
}

Max7221::~Max7221() {
}

void Max7221::init() {
	SPI.begin();
//	SPI.setClockDivider(SPI_CLOCK_DIV2);
	pinMode(selectPin, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(13, OUTPUT);
	send7221Command(MAX7221_COMMAND::test, false);
	send7221Command(MAX7221_COMMAND::intensity, 0x01);
	send7221Command(MAX7221_COMMAND::decode, false);
	send7221Command(MAX7221_COMMAND::scanLimit, 7);
	send7221Command(MAX7221_COMMAND::enable, true);
}

void Max7221::setIntensity(byte value0_15) {
	send7221Command(MAX7221_COMMAND::intensity, value0_15);
}

void Max7221::setScanLimit(byte lines0_7) {
	send7221Command(MAX7221_COMMAND::intensity, lines0_7);
}

void Max7221::setEnabled(bool on) {
	send7221Command(MAX7221_COMMAND::enable, on);
}

void Max7221::setTest(bool on) {
	send7221Command(MAX7221_COMMAND::enable, on);
}

void Max7221::setColumn(byte column, byte values) {
	send7221Command(MAX7221_COMMAND::digit0+(column % 8), values);
}

inline void Max7221::send7221Command(byte command, byte value)
{
   //2-byte data transfer to the 7221
	digitalWrite(selectPin, LOW);
	SPI.transfer(command);
	SPI.transfer(value);
	digitalWrite(selectPin, HIGH);
}

