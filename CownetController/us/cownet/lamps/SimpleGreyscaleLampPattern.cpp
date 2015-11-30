/*
 * SimpleSimpleGreyscaleLampPattern.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleGreyscaleLampPattern.h"

namespace us_cownet_lamps {

static bool inited = false;
// how many ticks in greyscale cycle
static int greyscaleCycleSize;
// mask for each bit in the cycle
static int mask[SimpleGreyscaleLampPattern::GREYSCALE_BITS];
// which pattern to use for each stage in the cycle
static int index[1 << SimpleGreyscaleLampPattern::GREYSCALE_BITS];

static void doInit() {
	if (!inited) {
		inited = true;
		//this section can be done once and statically initialized since GREYSCALE_BITS is constant
		greyscaleCycleSize = (1 << SimpleGreyscaleLampPattern::GREYSCALE_BITS) - 1;
		int next = 0;
		for (int i = 0; i < SimpleGreyscaleLampPattern::GREYSCALE_BITS; i++) {
			mask[i] = 1 << i;
			for (int j = 0; j < mask[i]; j++) {
				index[next++] = i;
			}
		}
	}
}

SimpleGreyscaleLampPattern::SimpleGreyscaleLampPattern()
: cycleCount(0), cycleStart(0), patterns()
{
}

SimpleGreyscaleLampPattern::SimpleGreyscaleLampPattern(int greyPattern[], int scratchSpaceIn[], int columnCount)
: cycleCount(0), cycleStart(0), patterns(), scratchSpace(scratchSpaceIn)
{
	setPattern(greyPattern, columnCount);
}

SimpleGreyscaleLampPattern::SimpleGreyscaleLampPattern(int greyPattern[], int scratchSpaceIn[], int columnCount, int startPosition)
: cycleCount(0), cycleStart(0), patterns(), scratchSpace(scratchSpaceIn)
{
	setPattern(greyPattern, columnCount, startPosition);
}

SimpleGreyscaleLampPattern::~SimpleGreyscaleLampPattern() {
}

byte SimpleGreyscaleLampPattern::getLampBank(int x) {
	return patterns[index[cycleCount]].getLampBank(x);
}

bool SimpleGreyscaleLampPattern::getLamp(int ndx) {
	return (getLampBank(ndx >> 3) & (1 << ndx)) != 0;
}

int SimpleGreyscaleLampPattern::getLampBankCount() {
	return patterns[0].getLampBankCount();
}

int SimpleGreyscaleLampPattern::getLampCount() {
	return patterns[0].getLampBankCount() * 8;
}

void SimpleGreyscaleLampPattern::setStartPosition(int startPosition) {
	cycleStart = startPosition;
}

void SimpleGreyscaleLampPattern::attached() {
	cycleCount = cycleStart;
}

void SimpleGreyscaleLampPattern::endOfMatrixSync() {
	cycleCount = (cycleCount + 1) % (greyscaleCycleSize);
}

void SimpleGreyscaleLampPattern::setPattern(int greyPattern[], int columnCount) {
	setPattern(greyPattern, columnCount, 0);
}

void SimpleGreyscaleLampPattern::setPattern(int greyPattern[], int lampCount, int startPosition) {
	doInit();

	// generate the actual component patterns
	cycleStart = startPosition;

	// generate the actual component patterns
	const int partitionSize = lampCount;				//one byte per column
	for (int i = 0; i < GREYSCALE_BITS; i++) {			//one matrix per greyscale bit
		int* patternStorage = scratchSpace + (partitionSize * i);
		patterns[i].setPattern(patternStorage, lampCount);
		for (int lampNdx = 0; lampNdx < lampCount; lampNdx++) {
			bool isOn = (greyPattern[lampNdx] & mask[i]) != 0;
			patterns[i].setLamp(lampNdx, isOn);
		}
	}
}

} /* namespace us_cownet_lamps */
