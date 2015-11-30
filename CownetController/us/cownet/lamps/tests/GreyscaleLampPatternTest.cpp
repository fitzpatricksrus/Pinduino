/*
 * GreyscaleLampPatternTest.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: jfitzpatrick
 */

#include "GreyscaleLampPatternTest.h"
#include "../AbstractGreyscaleLampPattern.h"
#include "../SimpleGreyscaleLampPattern.h"
#include "../../timers/TimerUtil.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::AbstractGreyscaleLampPattern;
using us_cownet_lamps::SimpleGreyscaleLampPattern;
using us_cownet_timers::TimerUtil;

// simple greyscale from lamp 0 - 63
class Pattern : public AbstractGreyscaleLampPattern {
public:
	Pattern(int* greyPatternIn)
	: AbstractGreyscaleLampPattern(0), greyPattern(greyPatternIn)
	{
	}

	Pattern(int* greyPattern, int startPosition)
	: AbstractGreyscaleLampPattern(startPosition), greyPattern(NULL)
	{
	}


	int getColCount() {
		return 8;
	}

	int getLampCount() {
		return getColCount()*8;
	}

	int getLampGreyValue(int ndx) {
		return greyPattern[ndx];
	}
private:
	int* greyPattern;
};

// pulsing lamp pattern
class Pattern2 : public AbstractGreyscaleLampPattern {
public:
	Pattern2()
	: AbstractGreyscaleLampPattern(0), position(0)
	{
	}

	Pattern2(int startPosition)
	: AbstractGreyscaleLampPattern(startPosition), position(0)
	{
	}

	int getLampBankCount() {
		return 8;
	}

	int getLampCount() {
		return getLampBankCount()*8;
	}

	int getLampGreyValue(int ndx) {
		int adj = abs(((position + ndx) % 128) - 64);	// -64..64
//			if (ndx == 0) {
//				System.out.println(Math.min(adj * 4, 255));
//			}
		return min(adj * 4, 255);
	}


	void greyscaleEndOfSync() {
		position = (position + 1) % 128;
	}

private:
		int position;
};

static int patternValues[] = {
	0, 1, 3, 7, 15, 31, 63, 127,
	0, 5, 10, 15, 20, 25, 30, 35,
	40, 45, 50, 55, 60, 65, 70, 75,
	80, 85, 90, 95, 100, 105, 110, 115,
	120, 125, 130, 135, 140, 145, 150, 155,
	160, 165, 170, 175, 180, 185, 190, 195,
	200, 205, 210, 215, 220, 225, 230, 235,
	240, 245, 250, 251, 252, 253, 254, 255
};
static int patternValues1[] = {
		1, 2, 4, 8, 16, 32, 64, 128,
		2, 4, 8, 16, 32, 64, 128, 1,
		4, 8, 16, 32, 64, 128, 1, 2,
		8, 16, 32, 64, 128, 1, 2, 4,
		16, 32, 64, 128, 1, 2, 4, 8,
		32, 64, 128, 1, 2, 4, 8, 16,
		64, 128, 1, 2, 4, 8, 16, 32,
		128, 1, 2, 4, 8, 16, 32, 64,
};
static int patternValues3[] = {
		1, 2, 4, 8, 1, 2, 4, 8,
		2, 4, 8, 1, 2, 4, 8, 1,
		4, 8, 1, 2, 4, 8, 1, 2,
		8, 1, 2, 4, 8, 1, 2, 4,
		4, 8, 1, 2, 4, 8, 1, 2,
		2, 4, 8, 1, 2, 4, 8, 1,
		1, 2, 4, 8, 1, 2, 4, 8,
		1, 2, 4, 8, 4, 2, 1, 0
};

static int scratch[64];

static Pattern testPattern1(patternValues1);
static Pattern testPattern2(patternValues);
static SimpleGreyscaleLampPattern testPattern3(patternValues3, &scratch[0], 8);

GreyscaleLampPatternTest::GreyscaleLampPatternTest(LampMatrix* greyMatrixIn)
: greyLampMatrix(greyMatrixIn)
{
}

GreyscaleLampPatternTest::~GreyscaleLampPatternTest() {
}

void GreyscaleLampPatternTest::setup() {
	int pos = 0;
	for (int col = 0; col < 8; col++) {
		for (int row = 0; row < 8; row++) {
			patternValues[(col << 3) + row] = 4 * pos++;
		}
	}

//		GreyscaleLampPattern pattern = new GreyscaleLampPattern(patternValues);
//		AbstractGreyscaleLampPattern pattern = new Pattern(patternValues);
	greyLampMatrix->setPattern(&testPattern2);
}

void GreyscaleLampPatternTest::loop() {
	TimerUtil::INSTANCE.tick();
}

} /* namespace us_cownet_lamps_tests */

