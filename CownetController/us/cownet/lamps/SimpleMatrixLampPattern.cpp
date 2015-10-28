/*
 * SimpleMatrixLampPattern.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleMatrixLampPattern.h"

namespace us_cownet_lamps {

SimpleMatrixLampPattern::SimpleMatrixLampPattern(int* patternIn, int columnCountIn)
: pattern(patternIn), columnCount(columnCountIn)
{
}

SimpleMatrixLampPattern::~SimpleMatrixLampPattern() {
}

int* SimpleMatrixLampPattern::getPattern() {
	return pattern;
}

void SimpleMatrixLampPattern::setPattern(int* newPattern) {
	pattern = newPattern;
}

bool SimpleMatrixLampPattern::getLamp(int col, int row) {
	return pattern[col*8+row];
}

void SimpleMatrixLampPattern::setLamp(int col, int row, bool on) {
	pattern[col*8+row] = on;
}

int SimpleMatrixLampPattern::getColCount() {
	return columnCount;
}

} /* namespace us_cownet_lamps */
