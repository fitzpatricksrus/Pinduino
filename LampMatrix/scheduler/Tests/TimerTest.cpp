/*
 * TimerTest.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: Dad
 */

#include "TimerTest.h"
#include "../../DirectOutputPins.h"
#include "../../SPIOutputPins.h"
#include "../Timer.h"

namespace scheduler {
namespace tests {

#ifdef __DEBUG__
#define debugln(x) if (Serial) Serial.debugln(x);
#define debug(x) if (Serial) Serial.debug(x);
#else
#define debugln(x)
#define debug(x)
#endif

TimerTest TimerTest::TEST;

static byte pins[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
static SPIOutputPins dop(8); //, pins);

static void timerTestCallback() {
	TimerTest::TEST.togglePins();
}

TimerTest::TimerTest() {

}

TimerTest::~TimerTest() {
}

static unsigned int delayValue = -1;

void TimerTest::setup() {
	debugln("TimerTest::setup");
	dop.initPins();
	for (int i = 0; i < dop.getPinCount(); i += 2) {
		dop.setPin(i, true);
	}
	dop.latch();

	Timer::TIMER1.init();
	Timer::TIMER1.setCallback(timerTestCallback, Timer::PS64, delayValue);
}
void TimerTest::loop() {
}

void TimerTest::togglePins() {
	for (int i = 0; i < dop.getPinCount(); i++) {
		if (dop.getPin(i)) {
			dop.setPin(i, false);
		} else {
			dop.setPin(i, true);
		}
	}
	dop.latch();
//	delayValue = delayValue << 1;
	if (delayValue == 0) delayValue = 1;
	Timer::TIMER1.setTicks(delayValue);
}

} /* namespace scheduler_test */
}
