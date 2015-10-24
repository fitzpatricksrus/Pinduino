/*
 * SimpleLampPattern.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: Dad
 */

#include "SimpleLampPattern.h"

namespace us_cownet_lamps {

SimpleLampPattern::SimpleLampPattern(int* patternIn, int columnCountIn)
: columnCount(columnCountIn), pattern(patternIn)
{
}

SimpleLampPattern::~SimpleLampPattern() {
}

int* SimpleLampPattern::getPattern() {
	return pattern;
}

void SimpleLampPattern::setPattern(int* newPattern) {
	pattern = newPattern;
}

byte SimpleLampPattern::getColumn(int col) {
	return (byte)pattern[col];
}

void SimpleLampPattern::setLamp(int col, int row, boolean on) {
	if (on) {
		pattern[col] |= (1 << row);
	} else {
		pattern[col] &= ~(1 << row);
	}
}

int SimpleLampPattern::getColCount() {
	return columnCount;
}

void SimpleLampPattern::attached() {
}

void SimpleLampPattern::endOfMatrixSync() {
}

bool SimpleLampPattern::isDone() {
	// repeat forever
	return false;
}

void SimpleLampPattern::reset() {
}

void SimpleLampPattern::detached() {
}

void SimpleLampPattern::allOn() {
	int* p = getPattern();
	for (int i = 0; i < columnCount; i++) {
		p[i] = -1;
	}
}

void SimpleLampPattern::allOff() {
	int* p = getPattern();
	for (int i = 0; i < columnCount; i++) {
		p[i] = 0;
	}
}

void SimpleLampPattern::unionPattern(LampPattern* other) {
	int colCount = min(getColCount(), other->getColCount());
	for (int col = 0; col < colCount; col++) {
		for (int row = 0; row < 8; row++) {
			if (!getLamp(col, row)) {
				setLamp(col, row, other->getLamp(col, row));
			}
		}
	}
}

void SimpleLampPattern::differencePattern(LampPattern* other) {
	// hey jf - this method doesn't deal with column counts correctly
	int colCount = min(getColCount(), other->getColCount());
	for (int col = 0; col < colCount; col++) {
		for (int row = 0; row < 8; row++) {
			setLamp(col, row, getLamp(col, row) != other->getLamp(col, row));
		}
	}
}

} /* namespace us_cownet_lamps */
