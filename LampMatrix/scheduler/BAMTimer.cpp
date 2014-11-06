/*
 * BAMTimer.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: Dad
 */

#include "BAMTimer.h"

namespace scheduler {

static const byte mask[] = { 0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000 };

BAMTimer::BAMTimer(Timer* timerIn, Callback* callbackIn)
: bitInCycle(0), timer(timerIn), callback(callbackIn)
{
}

BAMTimer::~BAMTimer() {
}

void BAMTimer::enableCallbacks() {
	timer->addCallback(this);
}

void BAMTimer::disableCallbacks() {
	timer->removeCallback(this);
}

void BAMTimer::setup() {
	bitInCycle = 0;
}

void BAMTimer::loop() {
	// start the next cycle right away and then call ISR
	timer->setTicks(mask[bitInCycle]);
	callback->loop(bitInCycle, mask[bitInCycle]);
	bitInCycle = (bitInCycle + 1) & 0b00000111;
}

} // end namespace scheduler
