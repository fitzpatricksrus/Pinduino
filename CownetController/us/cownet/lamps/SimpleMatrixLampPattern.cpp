/*
 * SimpleMatrixLampPattern.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleMatrixLampPattern.h"

namespace us_cownet_lamps {

SimpleMatrixLampPattern::SimpleMatrixLampPattern()
: pattern(NULL), columnCount(0)
{
}

SimpleMatrixLampPattern::SimpleMatrixLampPattern(int* patternIn, int columnCountIn)
: pattern(patternIn), columnCount(columnCountIn)
{
}

SimpleMatrixLampPattern::~SimpleMatrixLampPattern() {
}

int* SimpleMatrixLampPattern::getPattern() {
	return pattern;
}

void SimpleMatrixLampPattern::setPattern(int* newPattern, int columnCountIn) {
	columnCount = columnCountIn;
	pattern = newPattern;
}

byte SimpleMatrixLampPattern::getColumn(int col) {
	return pattern[col];
}

bool SimpleMatrixLampPattern::getLamp(int col, int row) {
	return (pattern[col] & (1 << row)) != 0;
}

void SimpleMatrixLampPattern::setLamp(int col, int row, bool on) {
	if (on) {
		pattern[col] |= (1 << row);
	} else {
		pattern[col] &= ~(1 << row);
	}
}

int SimpleMatrixLampPattern::getColCount() {
	return columnCount;
}

} /* namespace us_cownet_lamps */
