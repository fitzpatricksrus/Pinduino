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


static TimerUtil bla = TimerUtil();
TimerUtil& TimerUtil::INSTANCE = bla;



} /* namespace us_cownet_timers */

us_cownet_timers::TimerUtil::TimerUtil() {
}

us_cownet_timers::TimerUtil::~TimerUtil() {
}

void us_cownet_timers::TimerUtil::attachTickerCallback(Callback* callback,
		unsigned long ticks) {
}

void us_cownet_timers::TimerUtil::detachTickerCallback(Callback* callback) {
}

void us_cownet_timers::TimerUtil::attachTimerCallback(Callback* callback,
		unsigned long micros) {
}

void us_cownet_timers::TimerUtil::detachTimerCallback(Callback* callback) {
}

void us_cownet_timers::TimerUtil::tick() {
}

void us_cownet_timers::TimerUtil::enableHackTicks(bool userHacks) {
}

unsigned long us_cownet_timers::TimerUtil::currentTimeMillis() {
}

unsigned long us_cownet_timers::TimerUtil::currentTimeMicros() {
}

unsigned long us_cownet_timers::TimerUtil::currentTicks() {
}
