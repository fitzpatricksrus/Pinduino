/*
 * GreyscaleLampPattern.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#include "GreyscaleLampPattern.h"

namespace us_cownet_lamps_patterns {

GreyscaleLampPattern::GreyscaleLampPattern()
: lampCount(0), lampData(0)
{
}

GreyscaleLampPattern::GreyscaleLampPattern(byte* lampDataIn, int lampCountIn)
: lampCount(lampCountIn), lampData(lampDataIn)
{
}

GreyscaleLampPattern::~GreyscaleLampPattern() {
}

int GreyscaleLampPattern::getLampCount() {
	return lampCount;
}

bool GreyscaleLampPattern::getLamp(int index) {
	return lampData[index] != 0;
}

byte GreyscaleLampPattern::getGreyLamp(int index) {
	return lampData[index];
}

void GreyscaleLampPattern::setGreyLamp(int index, byte value) {
	lampData[index] = value;
}

byte* GreyscaleLampPattern::getLampData() {
	return lampData;
}

void GreyscaleLampPattern::setLampData(byte* lampDataIn, int lampCountIn) {
	lampCount = lampCountIn;
	lampData = lampDataIn;
}

RGBColor GreyscaleLampPattern::getRGBLamp(int index) {
	return RGBColor(lampData[index]);
}

} /* namespace us_cownet_lamps_patterns */
