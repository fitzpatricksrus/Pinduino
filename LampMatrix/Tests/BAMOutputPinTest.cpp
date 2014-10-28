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
#include "../scheduler/Timer.h"
#include "Debug.h"

namespace Tests {

static byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
//static byte brightness[] = { 255, 64, 4, 0, 4, 64, 255, 128 };
//static byte brightness[] = { 255, 127, 63, 31, 15, 7, 3, 0, 3, 7, 15, 31, 63, 127 };
//static byte brightness[] = { B11111111, B01111111, B00111111, B00011111, B00001111, B00000111, B00000011, B00000001,
//		B00000000, B00000000, B00000001, B00000011, B00000111, B00001111, B00011111, B00111111, B01111111, B11111111 };
static byte brightness[] = {
		B11111111,
		B01111111,
//		B01111111,
		B00111111,
//		B00111111,
		B00011111,
//		B00011111,
		B00001111,
//		B00001111,
		B00000111,
//		B00000111,
		B00000011,
//		B00000011,
		B00000001,
//		B00000001,
		B00000000,
		B00000000,
		B00000001,
//		B00000001,
		B00000011,
//		B00000011,
		B00000111,
//		B00000111,
		B00001111,
//		B00001111,
		B00011111,
//		B00011111,
		B00111111,
//		B00111111,
		B01111111,
//		B01111111,
		B11111111
};
//static byte values[] = { 255, 255, 255, 255, 255, 255, 255, 255 };
//static byte brightness[512];
static byte brightnessCount = 18;

static DirectOutputPins dopins(8, pins);
static BAMOutputPins spipins(&dopins);

BAMOutputPinTest::BAMOutputPinTest() {
}

BAMOutputPinTest::~BAMOutputPinTest() {
}

void BAMOutputPinTest::setup() {
	dopins.initPins();
	dopins.latch();
	spipins.latch();
	scheduler::Timer::timer1.init();
	Serial << " cycles: " << spipins.cycleCount << " on: " << spipins.cyclesOn << " %: " << (spipins.cyclesOn * 100 / spipins.cycleCount) << endl ;
}

static int count = 0;
static unsigned long lastLoop = 0;
void BAMOutputPinTest::loop() {
	scheduler::Timer::tickDebugTimer(micros());
	if ((millis() - lastLoop) > 10) {
		count = (count + 1) % 0x1FF;
		byte value = ((count) < 256) ? count : (512 - count);
		for (int i = 0; i < 8; i++) {
			spipins.setPin(i, value);
		}
		lastLoop = millis();
	}
}

BAMOutputPinTest BAMOutputPinTest::TEST;

} /* namespace Tests */
