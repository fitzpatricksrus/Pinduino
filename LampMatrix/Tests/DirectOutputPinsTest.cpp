/*
 * DirectOutputPinsTest.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#include "DirectOutputPinsTest.h"
#include "../DirectOutputPins.h"
#include "Arduino.h"

DirectOutputPinsTest DirectOutputPinsTest::TEST;

byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
DirectOutputPins dop(8, pins);

DirectOutputPinsTest::DirectOutputPinsTest() {
}

DirectOutputPinsTest::~DirectOutputPinsTest() {
}

void DirectOutputPinsTest::setup() {
	dop.initPins();
}

void DirectOutputPinsTest::loop() {
	for (int i = 0; i < dop.getPinCount(); i++) {
		dop.setPin(i, true);
	}
	dop.latch();
	delay(500);
	for (int i = 0; i < dop.getPinCount(); i++) {
		dop.setPin(i, false);
	}
	dop.latch();
	delay(500);
	for (int i = 0; i < dop.getPinCount(); i++) {
		dop.setPin(max(i - 1, 0), false);
		dop.setPin(i, true);
		delay(100);
	}
	for (int i = dop.getPinCount() - 2; i >= 0; i--) {
		dop.setPin(i + 1, false);
		dop.setPin(i, true);
		delay(100);
	}
	dop.setPin(0, false);
	delay(100);
}
