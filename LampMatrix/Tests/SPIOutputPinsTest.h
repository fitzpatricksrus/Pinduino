/*
 * SPIOutputPinsTest.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#ifndef SPIOUTPUTPINSTEST_H_
#define SPIOUTPUTPINSTEST_H_

#include "TestClass.h"

/*
 * This test runs on pins 2, 3, 4, 5, 6, 7, 8, 9
 * in various different orders repeatedly.
 */
class SPIOutputPinsTest : public TestClass {
public:
	SPIOutputPinsTest();
	virtual ~SPIOutputPinsTest();
	virtual void setup();
	virtual void setAllPins(bool setAllOn);
	virtual void loop();

	static SPIOutputPinsTest TEST;
};

#endif /* SPIOUTPUTPINSTEST_H_ */
