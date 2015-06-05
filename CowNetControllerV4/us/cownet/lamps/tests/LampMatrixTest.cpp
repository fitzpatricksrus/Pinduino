/*
 * LampMatrixTest.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "LampMatrixTest.h"
#include "../simple/SimpleLampPattern.h"
#include "../../timers/TimerUtil.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps_simple::SimpleLampPattern;
using us_cownet_timers::TimerUtil;

LampMatrixTest::LampMatrixTest(LampMatrix* matrixIn)
: matrix(matrixIn)
{
}

LampMatrixTest::~LampMatrixTest() {
}

static byte patternValues[] = {
		0b10000000,
		0b01000001,
		0b00100010,
		0b00010100,
		0b00001000,
		0b00010100,
		0b00100010,
		0b01000001,
};
static SimpleLampPattern pattern(patternValues);
void LampMatrixTest::setup() {
	matrix->setPattern(&pattern);
}

void LampMatrixTest::loop() {
	TimerUtil::TIMERS.hackTick();
}

} /* namespace us_cownet_lamps_tests */
