/*
 * SPILampMatrixTest.h
 *
 *  Created on: Oct 13, 2014
 *      Author: Dad
 */

#ifndef SPILAMPMATRIXTEST_H_
#define SPILAMPMATRIXTEST_H_

#include "TestClass.h"

namespace Tests {

class SPILampMatrixTest : public TestClass {
public:
	SPILampMatrixTest();
	virtual ~SPILampMatrixTest();

	virtual void setup();
	virtual void loop();

	static SPILampMatrixTest TEST;
};

} /* namespace Tests */

#endif /* SPILAMPMATRIXTEST_H_ */
