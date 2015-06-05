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

static const unsigned long delayPeriod = 200 * 1000;

WpcOutputControllerTest::WpcOutputControllerTest()
: hardware(NULL), ownedHardware(NULL), row(0), col(0), ticks(delayPeriod)
{
}

WpcOutputControllerTest::WpcOutputControllerTest(WpcOutputController* testController)
: hardware(testController), ownedHardware(NULL), row(0), col(0), ticks(delayPeriod)
{
}

WpcOutputControllerTest::~WpcOutputControllerTest() {
	delete ownedHardware;
}

void WpcOutputControllerTest::setup() {
	if (hardware == NULL) {
		// initialize the output pins
		byte dataPins[] = { 1 };
		byte signalPins[] = { 1 } ;
		hardware = new WpcOutputController(dataPins, signalPins);
		ownedHardware = hardware;
	}
}

void WpcOutputControllerTest::loop() {
	TimerUtil::TIMERS.hackTick();
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
