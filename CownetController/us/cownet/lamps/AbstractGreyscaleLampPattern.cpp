/*
 * AbstractGreyscaleLampPattern.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: jfitzpatrick
 */

#include "AbstractGreyscaleLampPattern.h"

namespace us_cownet_lamps {

// how many ticks in greyscale cycle
static const int greyscaleCycleSize = (1 << AbstractGreyscaleLampPattern::GREYSCALE_BITS) - 1;
// mask for each bit in the cycle
static int mask[greyscaleCycleSize];

static bool inited = false;
static void staticInit() {
	if (!inited) {
		inited = true;
		int next = 0;
		for (int i = 0; i < AbstractGreyscaleLampPattern::GREYSCALE_BITS; i++) {
			int m = (1 << i);
			for (int j = 0; j < m; j++) {
				mask[next++] = m;
			}
		}
	}
}

AbstractGreyscaleLampPattern::AbstractGreyscaleLampPattern()
: cycleCount(0), cycleStart(0)
{
	staticInit();
}

AbstractGreyscaleLampPattern::AbstractGreyscaleLampPattern(int startPosition)
: cycleCount(0), cycleStart(startPosition)
{
	staticInit();
}

AbstractGreyscaleLampPattern::~AbstractGreyscaleLampPattern() {
}

byte AbstractGreyscaleLampPattern::getColumn(int x) {
	byte result = 0;
	for (int i = getColCount() - 1; i >= 0; i--) {
		result <<= 1;
		if (getLamp(x, i)) {
			result |= 1;
		}
	}
	return result;
}

bool AbstractGreyscaleLampPattern::getLamp(int col, int row) {
	return getLamp((col << 3) + row);
}

bool AbstractGreyscaleLampPattern::getLamp(int index) {
	return (getLampGreyValue(index) & mask[cycleCount]) != 0;
}

void AbstractGreyscaleLampPattern::setStartPosition(int startPosition) {
	cycleStart = startPosition;
}

void AbstractGreyscaleLampPattern::attached() {
	cycleCount = cycleStart;
}

void AbstractGreyscaleLampPattern::endOfMatrixSync() {
	cycleCount = (cycleCount + 1) % (greyscaleCycleSize);
	if (cycleCount == 0) {
		greyscaleEndOfSync();
	}
}

void AbstractGreyscaleLampPattern::greyscaleEndOfSync() {
}

void AbstractGreyscaleLampPattern::setCycleStartPosition(int startPosition) {
	cycleStart = startPosition;
}

} /* namespace us_cownet_lamps */
