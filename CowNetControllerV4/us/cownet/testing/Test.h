/*
 * Test.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TESTING_TEST_H_
#define US_COWNET_TESTING_TEST_H_

namespace us_cownet_testing {

class Test {
public:
	Test();
	virtual ~Test();

	virtual void setup() = 0;
	virtual void loop() = 0;
};

} /* namespace us_cownet_testing */

#endif /* US_COWNET_TESTING_TEST_H_ */
