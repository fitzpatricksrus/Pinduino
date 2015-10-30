/*
 * LampMatrixTest.h
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#ifndef us_cownet_lamps_tests_LAMPMATRIXTEST_H_
#define us_cownet_lamps_tests_LAMPMATRIXTEST_H_

#include "../LampMatrix.h"
#include "../../testing/Test.h"

namespace us_cownet_lamps_tests {

using namespace::us_cownet_lamps;
using us_cownet_testing::Test;

class LampMatrixTest : public Test {
public:

	LampMatrixTest(LampMatrix* matrixIn);

	virtual ~LampMatrixTest();

	virtual void setup();

	virtual void loop();

	static LampMatrix* createTestMatrix();


private:
	LampMatrix* matrix;
};

} /* namespace us_cownet_lamps_tests */

#endif /* LAMPMATRIXTEST_H_ */
