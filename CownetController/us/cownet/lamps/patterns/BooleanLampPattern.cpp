/*
 * BooleanLampPattern.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#include "BooleanLampPattern.h"

#include <debug.h>

namespace us_cownet_lamps_patterns {

BooleanLampPattern::BooleanLampPattern()
: lampCount(0), lampData(NULL) {
}

BooleanLampPattern::BooleanLampPattern(byte* data, int lampCountIn)
: lampCount(lampCountIn), lampData(data) {
}

BooleanLampPattern::~BooleanLampPattern() {
}

int BooleanLampPattern::getLampCount() {
	return lampCount;
}

bool BooleanLampPattern::getLamp(int index) {
	int byteNdx = (index >> 3) & 0b00011111;
	int mask = 1 << (index & 0b00000111);
	return (lampData[byteNdx] & mask) != 0;
}

byte BooleanLampPattern::getLampBank(int bankIndex) {
	return lampData[bankIndex];
}

void BooleanLampPattern::setLamp(int index, bool on) {
	int byteNdx = (index >> 3) & 0b00011111;
	int mask = 1 << (index & 0b00000111);
	if (on) {
		lampData[byteNdx] |= mask;
	} else {
		lampData[byteNdx] &= (~mask);
	}
}

void BooleanLampPattern::setLampData(byte* lampDataIn, int lampCountIn) {
	lampData = lampDataIn;
	lampCount = lampCountIn;
	Serial << "lampCount = "<<lampCount<<" lampData[] = {";
	int stop = (lampCount + 7) / 8;
	for (int i = 0; i < stop; i++) {
		Serial << lampData[i] << ",";
	}
	Serial << "}" << endl;
}

byte* BooleanLampPattern::getLampData() {
	return lampData;
}

byte BooleanLampPattern::getGreyLamp(int index) {
	return getLamp(index) ? 255 : 0;
}

RGBColor BooleanLampPattern::getRGBLamp(int index) {
	return RGBColor(getLamp(index));
}

} /* namespace us_cownet_lamps_patterns */
