/*
 * WpcOutputControllerTest.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_WPC_TESTS_WPCOUTPUTCONTROLLERTEST_H_
#define US_COWNET_LAMPS_WPC_TESTS_WPCOUTPUTCONTROLLERTEST_H_

#include "../WpcOutputController.h"
#include "../../../testing/Test.h"
#include "../../../testing/Ticker.h"

namespace us_cownet_lamps_wpc_tests {

using namespace us_cownet_lamps_wpc;
using namespace us_cownet_testing;

class WpcOutputControllerTest : public Test {
public:
	WpcOutputControllerTest();
	WpcOutputControllerTest(WpcOutputController* testController);
	virtual ~WpcOutputControllerTest();

	virtual void setup();
	virtual void loop();

private:
	WpcOutputController* hardware;
	WpcOutputController* ownedHardware;
	int row;
	int col;
	Ticker ticks;
};

} /* namespace us_cownet_lamps_wpc_test */

#endif /* US_COWNET_LAMPS_WPC_TESTS_WPCOUTPUTCONTROLLERTEST_H_ */