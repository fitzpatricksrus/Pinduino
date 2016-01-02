/*
 * RGBLampPattern.cpp
 *
 *  Created on: Jan 1, 2016
 *      Author: Dad
 */

#include "RGBLampPattern.h"

namespace us_cownet_lamps_patterns {

RGBLampPattern::RGBLampPattern()
: lampCount(0), lampData(0)
{
}

RGBLampPattern::RGBLampPattern(RGBColor* lampDataIn, int lampCountIn)
: lampCount(lampCountIn), lampData(lampDataIn)
{
}

RGBLampPattern::~RGBLampPattern() {
}

int RGBLampPattern::getLampCount() {
	return lampCount;
}

bool RGBLampPattern::getLamp(int index) {
	return lampData[index].asBoolean();
}

byte RGBLampPattern::getGreyLamp(int index) {
	return lampData[index].asGreyscale();
}

RGBColor RGBLampPattern::getRGBLamp(int index) {
	return lampData[index];
}

void RGBLampPattern::setRGBLamp(int index, RGBColor color) {
	lampData[index] = color;
}

RGBColor* RGBLampPattern::getLampData() {
	return lampData;
}

void RGBLampPattern::setLampData(RGBColor* lampDataIn, int lampCountIn) {
	lampCount = lampCountIn;
	lampData = lampDataIn;
}

} /* namespace us_cownet_lamps_patterns */
