/*
 * MAX7221Pins.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: Dad
 */

#include "MAX7221Pins.h"
#include <Arduino.h>
#include "../SPI.h"

enum COMMAND {
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

void MAX7221Pins::send7221Command(byte command, byte value)
{
   digitalWrite(DS_Pin,LOW); //chip select is active low
   //2-byte data transfer to the 7221
   SPI.transfer(command);
   SPI.transfer(value);
   digitalWrite(DS_Pin,HIGH); //release chip, signal end transfer
}



MAX7221Pins::MAX7221Pins(byte slaveSelectPin_ST_CP, byte clockPin_SH_CP, byte dataPin_DS)
: ST_CP_Pin(slaveSelectPin_ST_CP), SH_CP_Pin(clockPin_SH_CP), DS_Pin(dataPin_DS)
{
	for (byte i = 0; i < 8; i++) {
		for (byte j = 0; j < 8; j++) {
			values[i][j] = 0;
		}
	}
}

MAX7221Pins::~MAX7221Pins() {
}

void MAX7221Pins::initPins() {
	pinMode(DS_Pin, OUTPUT);
	for (byte i = 0; i < 8; i++) {
		for (byte j = 0; j < 8; j++) {
			values[i][j] = 0;
		}
	}
	SPI.begin();
	//control->setIntensity(0x01);
	send7221Command(intensity, 0x01);

	//control->shutdown(false);
	send7221Command(enable, true);

}

byte MAX7221Pins::getRowCount() const {
	return 8;
}

byte MAX7221Pins::getColumnCount() const {
	return 8;
}

byte MAX7221Pins::getPin(byte col, byte row) const {
	return values[col][row];
}

void MAX7221Pins::setPin(byte col, byte row, bool pinValue) {
	values[col][row] = pinValue;
}

void MAX7221Pins::latch() {
	digitalWrite(DS_Pin, HIGH);
	for (int row = 0; row < 8; row++) {
		byte colValue = 0;
		for (int col = 0; col < 8; col++) {
			if (values[row][col]) {
				colValue |= (1 << col);
			}
		}
		send7221Command(digit0+row, colValue);
	}
	digitalWrite(DS_Pin, LOW);
}
