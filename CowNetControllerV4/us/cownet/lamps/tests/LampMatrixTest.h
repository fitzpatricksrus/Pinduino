/*
 * LampMatrixTest.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_TESTS_LAMPMATRIXTEST_H_
#define US_COWNET_LAMPS_TESTS_LAMPMATRIXTEST_H_

#include "../LampMatrix.h"
#include "../../testing/Test.h"
#include "../../testing/Ticker.h"

namespace us_cownet_lamps_tests {

using us_cownet_testing::Test;
using us_cownet_lamps::LampMatrix;

class LampMatrixTest : public Test {
public:
	LampMatrixTest(LampMatrix* matrix);
	virtual ~LampMatrixTest();

	virtual void setup();
	virtual void loop();

private:
	LampMatrix* matrix;
};

} /* namespace us_cownet_lamps_tests */

#endif /* US_COWNET_LAMPS_TESTS_LAMPMATRIXTEST_H_ */
