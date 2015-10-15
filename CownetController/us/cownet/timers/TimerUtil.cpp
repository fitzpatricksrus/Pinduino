/*
 * TimerUtil.cpp
 *
 *  Created on: Oct 13, 2015
 *      Author: Dad
 */

#include "TimerUtil.h"
#include "PeriodicEvent.h"
#include "Callback.h"
#include "../utils/Map.h"

namespace us_cownet_timers {

using us_cownet_utils::Map;

class CallbackHandler {
public:
	CallbackHandler(Callback* c, PeriodicEvent* e);

	void tick();

	Callback* c;
	PeriodicEvent* e;
};

CallbackHandler::CallbackHandler(Callback* cIn, PeriodicEvent* eIn) {
		c = cIn;
		e = eIn;
	}

void CallbackHandler::tick() {
	if (e->isTime()) {
		c->call();
	}
}



static Map<Callback, CallbackHandler, 20> callbackList;
static long ticks;

static TimerUtil INSTANCE = new TimerUtil();
static long REAL_TICKS = -1;



TimerUtil::TimerUtil() {
}

TimerUtil::~TimerUtil() {
}

void attachTickerCallback(Callback c, long ticks) {
	attachCallback(c, new Ticker(ticks));
}

void attachTimerCallback(Callback c, long micros) {
	attachCallback(c, new Timer(micros));
}

private void attachCallback(Callback c, PeriodicEvent p) {
	callbackList.put(c, new CallbackHandler(c, p));
}

void detachCallback(Callback c) {
	callbackList.put(c, null);
}

void tick() {
	ticks++;
	for (CallbackHandler handler : callbackList.values()) {
		handler.tick();
	}
}

void enableHackTicks(boolean useHacks) {
	useHackTicks = useHacks;
}

long currentTimeMillis() {
	return currentTimeMicros() / 1000;
}

long currentTimeMicros() {
	if (useHackTicks) {
		return currentTicks();
	} else {
		return System.nanoTime() / 1000;
	}
}

long currentTicks() {
	return ticks;
}

private TimerUtil() {
	callbackList = new HashMap<>();
	ticks = 0;
	useHackTicks = false;
}

private HashMap<Callback, CallbackHandler> callbackList;
private long ticks;
private boolean useHackTicks;

} /* namespace us_cownet_timers */
