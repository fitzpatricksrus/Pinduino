/*
 * SimpleLampMatrixTest.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "SimpleLampMatrixTest.h"

namespace us_cownet_lamps_tests {

SimpleLampMatrixTest::SimpleLampMatrixTest(PinballOutputController* controller, long micros)
: matrix(controller, micros)
{
}

SimpleLampMatrixTest::~SimpleLampMatrixTest() {
}

void SimpleLampMatrixTest::setup() {
	LampMatrixTest::setup();
}

void SimpleLampMatrixTest::loop() {
	LampMatrixTest::loop();
}

LampMatrix* SimpleLampMatrixTest::getMatrix() {
	return &matrix;
}

} /* namespace us_cownet_lamps_tests */
