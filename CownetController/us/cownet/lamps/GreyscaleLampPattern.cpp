/*
 * GreyscaleLampPattern.cpp
 */

#include "GreyscaleLampPattern.h"

namespace us_cownet_lamps {

GreyscaleLampPattern::GreyscaleLampPattern()
: cycleCount(0), cycleStart(0), patterns(), greyscaleCycleSize(0), mask(), index()
{
}

GreyscaleLampPattern::GreyscaleLampPattern(int greyPattern[], int scratchSpaceIn[], int columnCount)
: cycleCount(0), cycleStart(0), patterns(), greyscaleCycleSize(0), mask(), index(), scratchSpace(scratchSpaceIn)
{
	setPattern(greyPattern, columnCount);
}

GreyscaleLampPattern::GreyscaleLampPattern(int greyPattern[], int scratchSpaceIn[], int columnCount, int startPosition)
: cycleCount(0), cycleStart(0), patterns(), greyscaleCycleSize(0), mask(), index(), scratchSpace(scratchSpaceIn)
{
	setPattern(greyPattern, columnCount, startPosition);
}

GreyscaleLampPattern::~GreyscaleLampPattern() {
}

byte GreyscaleLampPattern::getColumn(int x) {
	return patterns[index[cycleCount]].getColumn(x);
}

int GreyscaleLampPattern::getColCount() {
	return patterns[0].getColCount();
}

void GreyscaleLampPattern::setStartPosition(int startPosition) {
	cycleStart = startPosition;
}

void GreyscaleLampPattern::attached() {
	cycleCount = cycleStart;
}

void GreyscaleLampPattern::endOfMatrixSync() {
	cycleCount = (cycleCount + 1) % (greyscaleCycleSize);
}

void GreyscaleLampPattern::setPattern(int greyPattern[], int columnCount) {
	setPattern(greyPattern, columnCount, 0);
}

void GreyscaleLampPattern::setPattern(int greyPattern[], int columnCount, int startPosition) {
	cycleStart = startPosition;

	//this section can be done once and statically initialized since GREYSCALE_BITS is constant
	greyscaleCycleSize = (1 << GREYSCALE_BITS) - 1;
	int next = 0;
	for (int i = 0; i < GREYSCALE_BITS; i++) {
		mask[i] = 1 << i;
		for (int j = 0; j < mask[i]; j++) {
			index[next++] = i;
		}
	}

	// generate the actual component patterns
	const int partitionSize = columnCount;
	for (int i = 0; i < GREYSCALE_BITS; i++) {
		int* patternStorage = scratchSpace + (partitionSize * i);
		patterns[i].setPattern(patternStorage, columnCount);
		for (int col = 0; col < columnCount; col++) {
			for (int row = 0; row < columnCount; row++) {
				bool isOn = (greyPattern[col * 8 + row] & mask[i]) != 0;
				patterns[i].setLamp(col, row, isOn);
			}
		}
	}
}

} /* namespace us_cownet_lamps */

