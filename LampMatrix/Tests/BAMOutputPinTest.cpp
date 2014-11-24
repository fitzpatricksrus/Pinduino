/*
 * BAMOutputPinTest.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: Dad
 */

#include "BAMOutputPinTest.h"

#include "../pins/SPIOutputPins.h"
#include "../pins/DirectOutputPins.h"
#include "../pins/BAMOutputPins.h"
#include "../pins/BOP.h"
#include "../scheduler/Timer.h"
#include "Debug.h"

namespace Tests {

static byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };

static scheduler::Timer2* timer = &scheduler::Timer2::INSTANCE;
static DirectOutputPins dpins(8, pins);
static BAMOutputPins dopins(timer, &dpins);
//static SPIOutputPins spins(8);
//static BAMOutputPins spipins(timer, &spins);

BAMOutputPinTest::BAMOutputPinTest() {
}

BAMOutputPinTest::~BAMOutputPinTest() {
}

void BAMOutputPinTest::setup() {
	timer->init();
	timer->setPrescalar(scheduler::Timer2::PS1024);
	timer->setTicks(1);
	timer->enableCallbacks();
	dpins.initPins();
	dpins.latch();
//	spins.initPins();
//	for (byte i = 0; i < 8; i++) {
//		spins.setPin(i, i % 2);
//	}
//	spins.latch();

	dopins.latch();
	dopins.setEnabled(true);
//	spipins.latch();
//	spipins.setEnabled(true);
}

static int count = 0;
static unsigned long lastLoop = 0;
//static byte splitter = 0;
void BAMOutputPinTest::loop() {

//	if ((splitter % 4) == 0)
//	scheduler::Timer::tickDebugTimer(micros());
//	splitter++;
	if ((micros() - lastLoop) > 2000) {
		count = (count + 1) & 0x1FF;
		for (int i = 0; i < 8; i++) {
			int val = count;
#if 0
			val = val & 0x1FF;
			val = (val < 256) ? val : (511 - val);
#else
			val = val & 0x1FF;
			val = (val + i*(512/8)) & 0x1FF;
			val = (val < 256) ? val : (511 - val);
#endif
			byte value = val;// / 4 * 4;
			dopins.setPin(i, value);
//			spipins.setPin(i, value);
		}
		dopins.latch();
//		spipins.latch();
		lastLoop = micros();
	}
}

BAMOutputPinTest BAMOutputPinTest::TEST;

} /* namespace Tests */
