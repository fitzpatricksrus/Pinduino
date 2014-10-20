/*
 * BAMOutputPinTest.h
 *
 *  Created on: Oct 18, 2014
 *      Author: Dad
 */

#ifndef BAMOUTPUTPINTEST_H_
#define BAMOUTPUTPINTEST_H_

#include "TestClass.h"

namespace Tests {

class BAMOutputPinTest : public TestClass {
public:
	BAMOutputPinTest();
	virtual ~BAMOutputPinTest();

	virtual void setup();
	virtual void loop();

	static BAMOutputPinTest TEST;
};

} /* namespace Tests */

#endif /* BAMOUTPUTPINTEST_H_ */
