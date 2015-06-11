/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <Arduino.h>
#include "Ticker.h"

namespace us_cownet_timers {

TimerUtil::TimerUtil()
: callback(NULL), ticker(0), hackMicros(-1)
{
}

TimerUtil::~TimerUtil() {
}

bool TimerUtil::attachInterrupt(Callback* callbackIn, long microsecondsIn) {
	callback = callbackIn;
	ticker.setPeriod((unsigned long)microsecondsIn);
	return true;
}

void TimerUtil::detachInterrupt(Callback* callbackIn) {
	callback = NULL;
}

void TimerUtil::hackTick() {
	if (callback != NULL && ticker.isTime()) {
		(*callback).call();
	}
}

void TimerUtil::hackTime(long timeInMicros) {
	hackMicros = timeInMicros;
}

long TimerUtil::currentTimeMillis() {
	return currentTimeMicros() * 1000;
}

long TimerUtil::currentTimeMicros() {
	if (hackMicros != -1) {
		return hackMicros;
	} else {
		return micros();
	}
}

static TimerUtil bla = TimerUtil();
TimerUtil& TimerUtil::INSTANCE = bla;


} /* namespace us_cownet_timers */
