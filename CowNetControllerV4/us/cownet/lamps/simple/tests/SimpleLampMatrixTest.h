/*
 * SimpleLampMatrixTest.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_SIMPLE_TESTS_SIMPLELAMPMATRIXTEST_H_
#define US_COWNET_LAMPS_SIMPLE_TESTS_SIMPLELAMPMATRIXTEST_H_

#include "../../PinballOutputController.h"
#include "../../tests/LampMatrixTest.h"
#include "../../simple/SimpleLampMatrix.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::PinballOutputController;
using us_cownet_lamps_simple::SimpleLampMatrix;

class SimpleLampMatrixTest: public us_cownet_testing::Test {
public:
	SimpleLampMatrixTest(PinballOutputController* controller, long micros);
	virtual ~SimpleLampMatrixTest();

	virtual void setup();
	virtual void loop();

private:
	SimpleLampMatrix matrix;
	LampMatrixTest test;
};

} /* namespace us_cownet_lamps_tests */

#endif /* US_COWNET_LAMPS_SIMPLE_TESTS_SIMPLELAMPMATRIXTEST_H_ */
