/*
 * SimpleLampPattern.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#include "SimpleLampPattern.h"

namespace us_cownet_lamps_simple {

SimpleLampPattern::SimpleLampPattern()
: pattern()
{
	for (byte i = 0; i < 8; i++) pattern[i] = 0;
}

SimpleLampPattern::~SimpleLampPattern() {
}

byte* SimpleLampPattern::getPattern() {
	return pattern;
}

void SimpleLampPattern::setPattern(byte pattern[]) {
	for (byte i = 0; i < 8; i++) this->pattern[i] = pattern[i];
}

bool SimpleLampPattern::getLamp(int col, int row) {
	return (pattern[col] & (1 << row)) != 0;
}

void SimpleLampPattern::setLamp(int col, int row, bool on) {
	if (on) {
		pattern[col] |= (1 << row);
	} else {
		pattern[col] &= ~(1 << row);
	}
}

} /* namespace us_cownet_lamps */
