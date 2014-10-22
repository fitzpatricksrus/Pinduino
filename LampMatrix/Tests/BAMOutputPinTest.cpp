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

static SPIOutputPins spipins2(8);
static DirectOutputPins spipins(8, pins);
static BAMOutputPins opins(&spipins);
static BAMOutputPins opins2(&spipins2);

BAMOutputPinTest::BAMOutputPinTest() {
}

BAMOutputPinTest::~BAMOutputPinTest() {
}

void BAMOutputPinTest::setup() {
	spipins.initPins();
	spipins2.initPins();
	for (int i = 0; i < 8; i++) {
		opins.setPin(i, brightness[0]);
		opins2.setPin(i, brightness[0]);
	}
	opins.latch();
	opins2.latch();
}

static byte count = 0;
static unsigned long lastLoop = 0;
void BAMOutputPinTest::loop() {
		if (millis() - lastLoop > 500) {
			for (int i = 0; i < 8; i++) {
				opins.setPin(i, count);
				opins2.setPin(i, count);
			}
			count = (count + 1) % 256;
			lastLoop = millis();
			Serial << count << endl ;
		}

/*	if (millis() - lastLoop > 58) {
		for (int i = 0; i < 8; i++) {
			opins.setPin(i, brightness[(count + 0 + i) % brightnessCount]);
			opins2.setPin(i, brightness[(count + 8 + i) % brightnessCount]);
		}
//		Serial << "Brightness: " << brightness[count] << endl;
		count = (count + 1) % brightnessCount;
		lastLoop = millis();
	} */
}

BAMOutputPinTest BAMOutputPinTest::TEST;

} /* namespace Tests */
