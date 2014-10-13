/*
 * DirectOutputPinsTest.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#ifndef DIRECTOUTPUTPINSTEST_H_
#define DIRECTOUTPUTPINSTEST_H_

#include "TestClass.h"

namespace Tests {

/*
 * This test runs on pins 2, 3, 4, 5, 6, 7, 8, 9
 * in various different orders repeatedly.
 */
class DirectOutputPinsTest : public TestClass {
public:
	DirectOutputPinsTest();
	virtual ~DirectOutputPinsTest();
	virtual void setup();
	virtual void loop();

	static DirectOutputPinsTest TEST;
};

}

#endif /* DIRECTOUTPUTPINSTEST_H_ */
