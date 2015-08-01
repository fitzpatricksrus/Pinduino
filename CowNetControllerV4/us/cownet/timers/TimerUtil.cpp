/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <Arduino.h>
#include "Ticker.h"
#include "../util/HashMap.h"

namespace us_cownet_timers {
using us_cownet_util::HashMap;

static TimerUtil bla = TimerUtil();
TimerUtil& TimerUtil::INSTANCE = bla;

static int hashLong(unsigned long l) {
	return l ^ (l >> 4) * 39;
}

static int hashPtr(void* p) {
	return hashLong((long)p);
}

TimerUtil::TimerUtil()
: tickers(hashLong), timers(hashLong), tickerCallbackList(hashPtr), timerCallbackList(hashPtr), ticks(0), useHackTicks(false)
{
}

TimerUtil::~TimerUtil() {
}

void TimerUtil::attachTickerCallback(Callback* callback, unsigned long ticks) {
	Ticker* ticker = tickers.get(ticks);
	if (ticker == NULL) {
		ticker = new Ticker(ticks);
		tickers.put(ticks, ticker);
		tickerCallbackList.put(ticker, new CallbackHandler());
	}
	CallbackHandler handler = tickerCallbackList.get(ticker);
	handler.addCallback(callback);
}

void TimerUtil::detachTickerCallback(Callback* callback) {
	for (CallbackHandler handler : tickerCallbackList.values()) {
		handler.removeCallback(callback);
		if (handler.isEmpty()) {
			// hey jf - it might be nice to do garbage collection of empty lists here.
		}
	}
}

void TimerUtil::attachTimerCallback(Callback* callback, unsigned long micros) {
}

void TimerUtil::detachTimerCallback(Callback* callback) {
}

void TimerUtil::tick() {
}

void TimerUtil::enableHackTicks(bool userHacks) {
}

unsigned long TimerUtil::currentTimeMillis() {
}

unsigned long TimerUtil::currentTimeMicros() {
}

unsigned long TimerUtil::currentTicks() {
}

TimerUtil::CallbackHandler::CallbackHandler() {
}

void TimerUtil::CallbackHandler::invokeCallbacks() {
	for (int i = 0; i < callbacks.size(); i++) {
		(*(callbacks[i]))();
	}
}

void TimerUtil::CallbackHandler::addCallback(Callback* c) {
	callbacks.add(c);
}

void TimerUtil::CallbackHandler::removeCallback(Callback* c) {
	callbacks.remove(c);
}

bool TimerUtil::CallbackHandler::isEmpty() {
	return callbacks.size() == 0;
}

}
