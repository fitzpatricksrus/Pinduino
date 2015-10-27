/*
 * LampMatrixTest.h
 *
 *  Created on: Oct 23, 2015
 *      Author: jfitzpatrick
 */

#ifndef LAMPMATRIXTEST_H_
#define LAMPMATRIXTEST_H_

#include "../LampMatrixTest.h"

namespace us_cownet_lamps_tests {

using namespace::us_cownet_lamps;

class LampMatrixTest {
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
