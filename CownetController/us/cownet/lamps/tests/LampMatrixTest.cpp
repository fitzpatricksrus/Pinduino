/*
 * LampMatrixTest.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#include "LampMatrixTest.h"

#include "../PinballOutputController.h"
#include "../PrefetchSimpleLampMatrix.h"
#include "../SimpleLampPattern.h"
#include "PinballOutputControllerTest.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::SimpleLampPattern;
using us_cownet_lamps::PrefetchSimpleLampMatrix;

static int patternValues[] = {
	0b10000001,
	0b01000010,
	0b00100100,
	0b00011000,
	0b00001000,
	0b00010100,
	0b00100010,
	0b01000001
};

static SimpleLampPattern pattern(patternValues, 8);

LampMatrixTest::LampMatrixTest(LampMatrix* matrixIn)
: matrix(matrixIn)
{
}

LampMatrixTest::~LampMatrixTest() {
}

void LampMatrixTest::setup() {
	Serial.println("LampMatrixTest::setup");
	matrix->setPattern(&pattern);
}

void LampMatrixTest::loop() {
//	Serial.println("LampMatrixTest::loop");
	TimerUtil::INSTANCE.tick();
}

LampMatrix* LampMatrixTest::createTestMatrix() {
	PinballOutputController* controller = PinballOutputControllerTest::createTestController();
	PrefetchSimpleLampMatrix* prefetchLampMatrix = new PrefetchSimpleLampMatrix(controller, 0);

	return prefetchLampMatrix;
}


} /* namespace us_cownet_lamps_tests */
