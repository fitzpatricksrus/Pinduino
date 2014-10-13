/*
 * SPIOutputPinsTest.cpp
 *
 *  Created on: Oct 12, 2014
 *      Author: Dad
 */

#include "SPIOutputPinsTest.h"

#include "../SPIOutputPins.h"
#include "Arduino.h"
#include "../SPI.h"

namespace Tests {

SPIOutputPinsTest SPIOutputPinsTest::TEST;
static byte SLAVE_PIN = 2;

static SPIOutputPins pins = SPIOutputPins(8).slaveSelectPin(SLAVE_PIN);

SPIOutputPinsTest::SPIOutputPinsTest() {
}

SPIOutputPinsTest::~SPIOutputPinsTest() {
}

void SPIOutputPinsTest::setup() {
	SPI.begin();
	pinMode(SLAVE_PIN, OUTPUT);
	setAllPins(false);
}

void SPIOutputPinsTest::setAllPins(bool value) {
	for (int i = 0; i < pins.getPinCount(); i++) {
		pins.setPin(i, value);
	}
	pins.latch();
}

void SPIOutputPinsTest::loop() {
	setAllPins(false);
	for (int i = 0; i < pins.getPinCount(); i++) {
		pins.setPin(i, true);
		pins.latch();
		delay(50);
	}
	for (int i = 0; i < pins.getPinCount(); i++) {
		pins.setPin(i, false);
		pins.latch();
		delay(50);
	}
	for (int i = pins.getPinCount() - 1; i >= 0; i--) {
		pins.setPin(i, true);
		pins.latch();
		delay(50);
	}
	for (int i = pins.getPinCount() - 1; i >= 0; i--) {
		pins.setPin(i, false);
		pins.latch();
		delay(50);
	}
}

}
