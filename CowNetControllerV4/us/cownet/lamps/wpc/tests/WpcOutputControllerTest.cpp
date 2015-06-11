/*
 * WpcOutputControllerTest.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "../tests/WpcOutputControllerTest.h"

#include "../../../timers/TimerUtil.h"

namespace us_cownet_lamps_wpc_tests {

using namespace us_cownet_timers;

static const unsigned long delayPeriod = 200L * 1000L;
//static const unsigned long delayPeriod = 200L;

WpcOutputControllerTest::WpcOutputControllerTest(WpcOutputController* testController)
: hardware(testController), row(0), col(0), ticks(delayPeriod)
{
}

WpcOutputControllerTest::~WpcOutputControllerTest() {
}

void WpcOutputControllerTest::setup() {
}

void WpcOutputControllerTest::loop() {
	TimerUtil::INSTANCE.hackTick();
	if (ticks.isTime()) {
		hardware->write(PinballOutputController::LAMP_COL, (byte)0);
		// set the row lamps
		hardware->write(PinballOutputController::LAMP_ROW, (byte)(1 << row));
		// turn the proper column back on
		hardware->write(PinballOutputController::LAMP_COL, (byte)(1 << col));

		row = row + 1;
		if (row >= 8) {
			row = 0;
			col = col + 1;
			if (col >= 8) {
				col = 0;
			}
		}
	}
}

} /* namespace us_cownet_lamps_wpc_test */
