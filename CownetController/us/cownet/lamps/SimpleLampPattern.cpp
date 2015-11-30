/*
 * SimpleLampPattern.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: Dad
 */

#include "SimpleLampPattern.h"

namespace us_cownet_lamps {

SimpleLampPattern::SimpleLampPattern()
: columnCount(0), pattern(NULL)
{
}

SimpleLampPattern::SimpleLampPattern(int* patternIn, int columnCountIn)
: columnCount(columnCountIn), pattern(patternIn)
{
}

SimpleLampPattern::~SimpleLampPattern() {
}

int* SimpleLampPattern::getPattern() {
	return pattern;
}

void SimpleLampPattern::setPattern(int* newPattern, int columnCountIn) {
	pattern = newPattern;
	columnCount = columnCountIn;
}

byte SimpleLampPattern::getColumn(int col) {
	return (byte)pattern[col];
}

int SimpleLampPattern::getLampCount() {
	return columnCount * 8;
}

bool SimpleLampPattern::getLamp(int ndx) {
	int col = ndx / 8;
	int row = ndx % 8;
	return (pattern[col] & (1 << row)) != 0;
}

void SimpleLampPattern::setLamp(int ndx, boolean on) {
	int col = ndx / 8;
	int row = ndx % 8;
	if (on) {
		pattern[col] |= (1 << row);
	} else {
		pattern[col] &= ~(1 << row);
	}
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
	int maxNdx = min(getLampCount(), other->getLampCount());
	for (int ndx = 0; ndx < maxNdx; ndx++) {
		if (!getLamp(ndx)) {
			setLamp(ndx, other->getLamp(ndx));
		}
	}
}

void SimpleLampPattern::differencePattern(LampPattern* other) {
	int maxNdx = min(getLampCount(), other->getLampCount());
	for (int ndx = 0; ndx < maxNdx; ndx++) {
		setLamp(ndx, getLamp(ndx) != other->getLamp(ndx));
	}
}

} /* namespace us_cownet_lamps */
