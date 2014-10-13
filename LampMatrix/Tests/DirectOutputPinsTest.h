/*
 * DirectOutputPinsTest.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#ifndef DIRECTOUTPUTPINSTEST_H_
#define DIRECTOUTPUTPINSTEST_H_

#include "TestClass.h"

class DirectOutputPinsTest : public TestClass {
public:
	DirectOutputPinsTest();
	virtual ~DirectOutputPinsTest();
	virtual void setup();
	virtual void loop();

	static DirectOutputPinsTest TEST;
};

#endif /* DIRECTOUTPUTPINSTEST_H_ */
