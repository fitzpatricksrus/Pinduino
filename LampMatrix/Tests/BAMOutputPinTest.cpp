/*
 * BAMOutputPinTest.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: Dad
 */

#include "BAMOutputPinTest.h"

#include "../SPIOutputPins.h"
#include "../DirectOutputPins.h"
#include "../BAMOutputPins.h"
#include "Debug.h"

namespace Tests {

static byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
//static byte values[] = { 255, 64, 4, 0, 4, 64, 255, 128 };
//static byte values[] = { 255, 255, 255, 255, 255, 255, 255, 255 };
static byte brightness[512];
static byte brightnessCount = 0;

//static SPIOutputPins spipins(8);
static DirectOutputPins spipins(8, pins);
static BAMOutputPins opins(&spipins);

BAMOutputPinTest::BAMOutputPinTest() {
}

BAMOutputPinTest::~BAMOutputPinTest() {
}

void BAMOutputPinTest::setup() {
	for (int i = -255; i < 255; i += 16) {
		brightness[brightnessCount] = abs(i);
		brightnessCount++;
	}

	spipins.initPins();
	for (int i = 0; i < 8; i++) {
		opins.setPin(i, brightness[0]);
	}
	opins.latch();
}

static byte count = 0;
static unsigned long lastLoop = 0;
void BAMOutputPinTest::loop() {
	if (millis() - lastLoop > 100) {
		for (int i = 0; i < 8; i++) {
			opins.setPin(i, brightness[count]);
		}
		Serial << "Brightness: " << brightness[count] << endl;
		count = (count + 1) % brightnessCount;
		lastLoop = millis();
	}
}

BAMOutputPinTest BAMOutputPinTest::TEST;

} /* namespace Tests */
