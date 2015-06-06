/*
 * SimpleLampMatrixTest.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "SimpleLampMatrixTest.h"

namespace us_cownet_lamps_tests {

SimpleLampMatrixTest::SimpleLampMatrixTest(PinballOutputController* controller, long micros)
: matrix(controller, micros), test(&matrix)
{
}

SimpleLampMatrixTest::~SimpleLampMatrixTest() {
}

void SimpleLampMatrixTest::setup() {
	test.setup();
}

void SimpleLampMatrixTest::loop() {
	test.loop();
}

} /* namespace us_cownet_lamps_tests */
