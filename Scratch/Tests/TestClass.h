/*
 * TestClass.h
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#ifndef TESTCLASS_H_
#define TESTCLASS_H_

namespace Tests {

class TestClass {
public:
	TestClass();
	virtual ~TestClass();

	virtual void setup() = 0;
	virtual void loop() = 0;
};

}
#endif /* TESTCLASS_H_ */
