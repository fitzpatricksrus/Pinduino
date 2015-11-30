/*
 * GreyscaleLampPattern.cpp
 */

#include "GreyscaleLampPattern.h"

namespace us_cownet_lamps {

static bool inited = false;
// how many ticks in greyscale cycle
static int greyscaleCycleSize;
// mask for each bit in the cycle
static int mask[GreyscaleLampPattern::GREYSCALE_BITS];
// which pattern to use for each stage in the cycle
static int index[1 << GreyscaleLampPattern::GREYSCALE_BITS];

static void doInit() {
	if (!inited) {
		inited = true;
		//this section can be done once and statically initialized since GREYSCALE_BITS is constant
		greyscaleCycleSize = (1 << GreyscaleLampPattern::GREYSCALE_BITS) - 1;
		int next = 0;
		for (int i = 0; i < GreyscaleLampPattern::GREYSCALE_BITS; i++) {
			mask[i] = 1 << i;
			for (int j = 0; j < mask[i]; j++) {
				index[next++] = i;
			}
		}
	}
}

GreyscaleLampPattern::GreyscaleLampPattern()
: cycleCount(0), cycleStart(0), patterns(), scratchSpace(NULL)
{
}

GreyscaleLampPattern::GreyscaleLampPattern(int greyPattern[], int scratchSpaceIn[], int columnCount, int startPosition)
: cycleCount(0), cycleStart(0), patterns(), scratchSpace(scratchSpaceIn)
{
	setPattern(greyPattern, scratchSpaceIn, columnCount, startPosition);
}

GreyscaleLampPattern::~GreyscaleLampPattern() {
}

int GreyscaleLampPattern::getLampBankCount() {
	return patterns[0].getLampBankCount();
}

byte GreyscaleLampPattern::getLampBank(int x) {
	return patterns[index[cycleCount]].getLampBank(x);
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

void GreyscaleLampPattern::setPattern(int greyPattern[], int scratchSpaceIn[], int lampCount, int startPosition) {
	doInit();

	// generate the actual component patterns
	scratchSpace = scratchSpaceIn;
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

