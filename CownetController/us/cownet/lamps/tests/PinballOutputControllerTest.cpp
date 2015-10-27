/*
 * PinballOutputControllerTest.cpp
 *
 *  Created on: Oct 26, 2015
 *      Author: jfitzpatrick
 */

#include "PinballOutputControllerTest.h"

#include "../controllers/WPCOutputController.h"

namespace us_cownet_lamps_tests {

PinballOutputControllerTest::PinballOutputControllerTest(PinballOutputController* testController)
: hardware(testController), row(0), col(0)
{
}

PinballOutputControllerTest::~PinballOutputControllerTest() {
}

void setup() {
}

void PinballOutputControllerTest::loop() {
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

static int controlPins[]  = { 2, 3 };
static int dataPins[] { 4, 5, 6, 7, 8, 9, 10, 11 };

PinballOutputController* PinballOutputControllerTest::createTestController() {
	return new us_cownet_lamps_controllers::WPCOutputController(dataPins, controlPins);
}

void PinballOutputControllerTest::main() {
	PinballOutputController* controller = PinballOutputControllerTest::createTestController();

	PinballOutputControllerTest test(controller);
//		test.execute(100L * 1000L);
	test.execute(10L * 1000L);
}


} /* namespace us_cownet_lamps_tests */
