/*
 * SimpleLampPattern.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#include "SimpleLampPattern.h"

namespace us_cownet_lamps_simple {

static SimpleLampPattern ALL_OFF_INSTANCE = SimpleLampPattern();
SimpleLampPattern& SimpleLampPattern::ALL_OFF = ALL_OFF_INSTANCE;

SimpleLampPattern::SimpleLampPattern()
: pattern(NULL), colCount(0)
{
}

SimpleLampPattern::SimpleLampPattern(byte patternIn[], byte colCountIn)
: pattern(patternIn), colCount(colCountIn)
{
}

SimpleLampPattern::~SimpleLampPattern() {
}

byte* SimpleLampPattern::getPattern() {
	return pattern;
}

void SimpleLampPattern::setPattern(byte patternIn[], byte colCount) {
	pattern = patternIn;
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

byte SimpleLampPattern::getColCount() {
	return colCount;
}

} /* namespace us_cownet_lamps */
