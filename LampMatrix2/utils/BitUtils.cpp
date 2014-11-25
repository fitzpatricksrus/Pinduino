/*
 * BitUtils.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: jfitzpatrick
 */

#include "BitUtils.h"

#include <Arduino.h>

namespace utils {

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))


void BitUtils::compressBits(byte bitCount, bool* bitsIn, byte* bytesOut) {
	for (int i = 0; i < bitCount; i++) {
		byte bit = i % 8;
		byte bite = i / 8;
		bytesOut[bite] = bitWrite(bytesOut[bite], bit, bitsIn[i]);
	}
}

void BitUtils::decompressBits(byte bitCount, byte* bytesIn, bool* bitsOut) {
	for (int i = 0; i < bitCount; i++) {
		byte bit = i % 8;
		byte bite = i / 8;
		bitsOut[i] = bitRead(bytesIn[bite], bit);
	}
}

byte BitUtils::masks[8] = {
		0b00000001,
		0b00000010,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01000000,
		0b10000000
};

byte BitUtils::notMasks[8] = {
		0b11111110,
		0b11111101,
		0b11111011,
		0b11110111,
		0b11101111,
		0b11011111,
		0b10111111,
		0b01111111
};

}
