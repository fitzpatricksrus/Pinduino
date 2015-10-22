/*
 * TimerUtil.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: Dad
 */

#include "TimerUtil.h"
#include "PeriodicEvent.h"
#include "Callback.h"
#include "../utils/List.h"
#include "../utils/Map.h"

#include <stdlib.h>

#include <Arduino.h>

namespace us_cownet_timers {

using us_cownet_utils::List;
using us_cownet_utils::Map;

TimerUtil::CallbackHandler::CallbackHandler() {
	c = NULL;
	e = PeriodicEvent::NEVER;
}

TimerUtil::CallbackHandler::CallbackHandler(Callback* cIn, PeriodicEvent eIn) {
	c = cIn;
	e = eIn;
}

void TimerUtil::CallbackHandler::tick() {
	if (e.isTime()) {
		c->call();
	}
}

static TimerUtil REAL_INSTANCE = TimerUtil();
TimerUtil& TimerUtil::INSTANCE = REAL_INSTANCE;
static TimerUtil::CallbackHandler NOT_FOUND_VALUE;

TimerUtil::TimerUtil()
: callbackList(NULL, NOT_FOUND_VALUE), ticks(0)
{
}

TimerUtil::~TimerUtil() {
}

void TimerUtil::attachTickerCallback(Callback* c, long ticks) {
	attachCallback(c, PeriodicEvent::forTicks(ticks));
}

void TimerUtil::attachTimerCallback(Callback* c, long micros) {
	attachCallback(c, PeriodicEvent::forTime(micros));
}

void TimerUtil::attachCallback(Callback* c, PeriodicEvent p) {
	callbackList.put(c, CallbackHandler(c, p));
}

void TimerUtil::detachCallback(Callback* c) {
	callbackList.put(c, NOT_FOUND_VALUE);
}

void TimerUtil::tick() {
	TimerUtil::ticks++;
	List<CallbackHandler, 10> values = callbackList.valueList;
	for (int i = 0; i < values.size(); i++) {
		CallbackHandler handler = values[i];
		handler.tick();
	}
}

long TimerUtil::currentTimeMillis() const {
	return millis();
}

unsigned long TimerUtil::currentTimeMicros() const {
	return micros();
}

long TimerUtil::currentTicks() const {
	return ticks;
}

} /* namespace us_cownet_timers */
