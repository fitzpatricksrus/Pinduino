/*
 * PinballOutputControllerTest.h
 *
 *  Created on: Oct 26, 2015
 *      Author: jfitzpatrick
 */

#ifndef PINBALLOUTPUTCONTROLLERTEST_H_
#define PINBALLOUTPUTCONTROLLERTEST_H_

#include "../PinballOutputController.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::PinballOutputController;

class PinballOutputControllerTest: us_cownet_testing::Test {
public:

	PinballOutputControllerTest(PinballOutputController* testController) ;

	PinballOutputControllerTest::~PinballOutputControllerTest();

	void setup();

	void loop();

	static PinballOutputController* createTestController();

	static void main();

private:
	PinballOutputController* hardware;
	int row;
	int col;
};

} /* namespace us_cownet_lamps_tests */

#endif /* PINBALLOUTPUTCONTROLLERTEST_H_ */
