/*
 * PeriodicEvent.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: jfitzpatrick
 */

#include "PeriodicEvent.h"

#include "TimerUtil.h"

namespace us_cownet_timers {

static const PeriodicEvent NEVER_INSTANCE = PeriodicEvent::forTime(-1);
const PeriodicEvent& PeriodicEvent::NEVER = NEVER_INSTANCE;

PeriodicEvent::PeriodicEvent()
: lastTock(0), period(0), isTicks(false)
{
}

PeriodicEvent::PeriodicEvent(const PeriodicEvent& other)
: lastTock(other.lastTock), period(other.period), isTicks(other.isTicks)
{
}

PeriodicEvent::PeriodicEvent(const PeriodicEvent&& other)
: lastTock(other.lastTock), period(other.period), isTicks(other.isTicks)
{
}

PeriodicEvent::~PeriodicEvent() {
}

PeriodicEvent& PeriodicEvent::operator=(const PeriodicEvent& other) {
	lastTock = other.lastTock;
	period = other.period;
	isTicks = other.isTicks;
	return *this;
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

PeriodicEvent PeriodicEvent::forTicks(long ticks) {
	PeriodicEvent e;
	e.setTicks(ticks);
	return e;
}

PeriodicEvent PeriodicEvent::forTime(long time) {
	PeriodicEvent e;
	e.setTime(time);
	return e;
}


} /* namespace us_cownet_timers */
