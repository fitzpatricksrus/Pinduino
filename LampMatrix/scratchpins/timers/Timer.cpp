/*
 * Timer.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#include "Timer.h"
#include <Arduino.h>

namespace timers {

void Timer::Callback::loop() {
}

void Timer::setTicks(unsigned int ticks) {
}

Timer::Timer()
	: callbackA(0), callbackB(0)
{
}

Timer::~Timer() {
}

void Timer::addCallback(Callback* callbackIn) {
	if (callbackA == 0) {
		callbackA = callbackIn;
	} else if (callbackB == 0) {
		callbackB = callbackIn;
	} else {
		// would be nice to throw an exception here
	}
}

void Timer::removeCallback(Callback* callbackIn) {
	if (callbackA == callbackIn) {
		callbackA = 0;
	} else if (callbackB == callbackIn) {
		callbackB = 0;
	} else {
		// would be nice to throw an exception here
	}
}

} /* namespace Tests */
