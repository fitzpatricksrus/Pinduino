/*
 * DirectOutputPinsTest.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#include "DirectOutputPinsTest.h"
#include "../DirectOutputPins.h"
#include "Arduino.h"
#include "Debug.h"

namespace Tests {

DirectOutputPinsTest DirectOutputPinsTest::TEST;

static byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static DirectOutputPins* dop;

DirectOutputPinsTest::DirectOutputPinsTest() {
}

DirectOutputPinsTest::~DirectOutputPinsTest() {
}

void DirectOutputPinsTest::setup() {
	debugScope(F("DirectOutputPinsTest::setup"));
	dop = new DirectOutputPins(8, pins);
	dop->initPins();
}


static void allOn() {
	for (int i = 0; i < dop->getPinCount(); i++) {
		dop->setPin(i, true);
	}
}

static void allOff() {
	for (int i = 0; i < dop->getPinCount(); i++) {
		dop->setPin(i, false);
	}
}

void DirectOutputPinsTest::loop() {
	debugScope(F("DirectOutputPinsTest::loop"));
	allOn();
	dop->latch();
	delay(500);

	allOff();
	dop->latch();
	delay(500);

	for (int i = 0; i < dop->getPinCount(); i++) {
		dop->setPin(max(i - 1, 0), false);
		dop->setPin(i, true);
		dop->latch();
		delay(100);
	}
	for (int i = dop->getPinCount() - 2; i >= 0; i--) {
		dop->setPin(i + 1, false);
		dop->setPin(i, true);
		dop->latch();
		delay(100);
	}
	dop->setPin(0, false);
	dop->latch();
	delay(100);

	dop->setAutoLatch(true);
	for (int i = 0; i < dop->getPinCount(); i++) {
		dop->setPin(max(i - 1, 0), false);
		dop->setPin(i, true);
		delay(100);
	}
	for (int i = dop->getPinCount() - 2; i >= 0; i--) {
		dop->setPin(i + 1, false);
		dop->setPin(i, true);
		delay(100);
	}
	dop->setPin(0, false);
	delay(100);
}

}
