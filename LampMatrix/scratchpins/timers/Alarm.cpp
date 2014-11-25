/*
 * Alarm.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: Dad
 */

#include "Alarm.h"

#include <stddef.h>

namespace timers {

Alarm::Alarm()
: callback(NULL)
{
}

Alarm::~Alarm() {
}

void Alarm::attachInterrupt(Callback* callbackIn) {
	callback = callbackIn;
}

void Alarm::detachInterrupt() {
	stop();
	callback = NULL;
}

void Alarm::setPeriod(unsigned long periodMs) {
	// Convert period in microseconds to frequency in Hz
	double frequency = 1000000.0 / periodMs;
	setFrequency(frequency);
}

void Alarm::doCallback() {
	callback->loop(*this);
}

void Alarm::Callback::loop(Alarm& alarm) {
}

} /* namespace timers */

