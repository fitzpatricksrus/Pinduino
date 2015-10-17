/*
 * PeriodicEvent.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: jfitzpatrick
 */

#include "PeriodicEvent.h"

#include "TimerUtil.h"

namespace us_cownet_timers {

PeriodicEvent::PeriodicEvent()
: lastTock(0), period(0), isTicks(false)
{
}

PeriodicEvent::~PeriodicEvent() {
}

void PeriodicEvent::setTicks(long ticks) {
	lastTock = 0;
	period = ticks;
	isTicks = true;
}

void PeriodicEvent::setTime(long time) {
	lastTock = 0;
	period = time;
	isTicks = false;
}

bool PeriodicEvent::isTime() {
	if (period == 0) {
		return true;
	}
	long now = (isTicks) ? TimerUtil::INSTANCE.currentTicks() : TimerUtil::INSTANCE.currentTimeMicros();
	if (now - lastTock > period) {
		lastTock = now;
		return true;
	} else {
		return false;
	}
}

} /* namespace us_cownet_timers */
