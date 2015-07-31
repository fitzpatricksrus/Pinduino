/*
 * Timer.cpp
 *
 *  Created on: Jul 28, 2015
 *      Author: jfitzpatrick
 */

#include "Timer.h"

#include "TimerUtil.h"

#include <Arduino.h>

namespace us_cownet_timers {

Timer::Timer(unsigned long periodMicrosIn)
: periodMicros(periodMicrosIn), lastMicro(0)
{
}

Timer::~Timer() {
}

void Timer::setPeriod(unsigned long periodInMicrosIn) {
	periodMicros = (periodInMicrosIn);
}

unsigned long Timer::getPeriod() {
	return periodMicros;
}

bool Timer::isTime() {
	unsigned long now = TimerUtil::INSTANCE.currentTimeMicros();
	if (now - lastMicro > periodMicros) {
		periodMicros = now;
		return true;
	} else {
		return false;
	}
}



} /* namespace us_cownet_timers */
