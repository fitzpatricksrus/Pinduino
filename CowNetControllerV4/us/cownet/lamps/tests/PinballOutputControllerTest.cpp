/*
 * PinballOutputControllerTest.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Dad
 */

#include "PinballOutputControllerTest.h"
#include "../../timers/TimerUtil.h"
#include <Debug.h>

namespace us_cownet_lamps_tests {

using us_cownet_timers::TimerUtil;

static const unsigned long delayPeriod = 200L * 1000L;

PinballOutputControllerTest::PinballOutputControllerTest(PinballOutputController* controllerIn)
: controller(controllerIn), row(0), col(0), ticks(delayPeriod)
{
}

PinballOutputControllerTest::~PinballOutputControllerTest() {
}

void PinballOutputControllerTest::setup() {
}

void PinballOutputControllerTest::loop() {
	TimerUtil::INSTANCE.tick();
	if (ticks.isTime()) {
//		Serial << "tick (" << col << ", " << row << ") ";
		controller->write(PinballOutputController::LAMP_COL, (byte)0);
//		Serial << "col(0) ";
		// set the row lamps
		controller->write(PinballOutputController::LAMP_ROW, (byte)(1 << row));
//		Serial << "row( " << (1 << row) <<") ";
		// turn the proper column back on
		controller->write(PinballOutputController::LAMP_COL, (byte)(1 << col));
//		Serial << "col( " << (1 << col) <<") " << endl;

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

} /* namespace us_cownet_lamps_tests */
