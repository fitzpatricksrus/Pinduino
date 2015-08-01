/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <Arduino.h>

namespace us_cownet_timers {

static TimerUtil bla = TimerUtil();
TimerUtil& TimerUtil::INSTANCE = bla;

TimerUtil::TimerUtil()
: callbackList(), size(0), ticks(0), useHackTicks(false)
{
}

TimerUtil::~TimerUtil() {
}

void TimerUtil::attachTickerCallback(Callback* callback, unsigned long ticks) {
	callbackList[size++] = CallbackEntry(callback, true, ticks);
}

void TimerUtil::attachTimerCallback(Callback* callback, unsigned long micros) {
	callbackList[size++] = CallbackEntry(callback, false, ticks);
}

void TimerUtil::detachCallback(Callback* callback) {
	for (int i = 0; i < size; i++) {
		if (callbackList[i].callback == callback) {
			size--;
			callbackList[i] = callbackList[size];
			return;
		}
	}
}

void TimerUtil::tick() {
	for (int i = 0; i < size; i++) {
		callbackList[i].tick();
	}
}

void TimerUtil::enableHackTicks(bool userHacks) {
	useHackTicks = userHacks;
}

unsigned long TimerUtil::currentTimeMillis() {
	return currentTimeMicros() / 1000;
}

unsigned long TimerUtil::currentTimeMicros() {
	if (useHackTicks) {
		return currentTicks();
	} else {
		return micros();
	}
}

unsigned long TimerUtil::currentTicks() {
	return ticks;
}


TimerUtil::CallbackEntry::CallbackEntry()
: callback(NULL), event(false, 0)
{
}
TimerUtil::CallbackEntry::CallbackEntry(Callback* c, bool isTicker, unsigned long period)
: callback(c), event(isTicker, period)
{
}

TimerUtil::CallbackEntry::CallbackEntry(const CallbackEntry& other)
: callback(other.callback), event(other.event)
{
}

void TimerUtil::CallbackEntry::tick() {
	if (event.isTime()) {
		callback->call();
	}
}

} // namespace

