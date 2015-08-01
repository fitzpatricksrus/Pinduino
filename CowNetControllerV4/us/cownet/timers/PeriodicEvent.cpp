/*
 * PeriodicEvent.cpp
 *
 *  Created on: Jul 31, 2015
 *      Author: Dad
 */

#include "PeriodicEvent.h"

#include "TimerUtil.h"

namespace us_cownet_timers {

PeriodicEvent::PeriodicEvent(bool isTickerIn, unsigned long periodIn)
: isTickerEvent(isTickerIn), period(periodIn), lastEvent(0)
{
}

PeriodicEvent::PeriodicEvent(const PeriodicEvent& other)
: isTickerEvent(other.isTickerEvent), period(other.period), lastEvent(0)
{
}

PeriodicEvent::~PeriodicEvent() {
}

bool PeriodicEvent::isTime() {
	unsigned long now = (isTickerEvent) ? TimerUtil::INSTANCE.currentTicks() : TimerUtil::INSTANCE.currentTimeMicros();
	if (now - lastEvent > period) {
		lastEvent = now;
		return true;
	} else {
		return false;
	}
}

} //namespace
