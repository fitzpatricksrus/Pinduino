/*
 * PinballOutputControllerTest.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_TESTS_PINBALLOUTPUTCONTROLLERTEST_H_
#define US_COWNET_LAMPS_TESTS_PINBALLOUTPUTCONTROLLERTEST_H_

#include "../PinballOutputController.h"
#include "../../testing/Test.h"
#include "../../testing/Ticker.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::PinballOutputController;
using us_cownet_testing::Test;
using us_cownet_testing::Ticker;

class PinballOutputControllerTest: public Test {
public:
	PinballOutputControllerTest(PinballOutputController* controllerIn);
	virtual ~PinballOutputControllerTest();

	virtual void setup();
	virtual void loop();

private:
	PinballOutputController* controller;
	int row;
	int col;
	Ticker ticks;
};

} /* namespace us_cownet_lamps_tests */

#endif /* US_COWNET_LAMPS_TESTS_PINBALLOUTPUTCONTROLLERTEST_H_ */
