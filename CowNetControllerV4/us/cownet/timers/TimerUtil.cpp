/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <Arduino.h>
#include "../testing/Ticker.h"

namespace us_cownet_timers {

using us_cownet_testing::Ticker;

TimerUtil::TimerUtil() {
}

TimerUtil::~TimerUtil() {
}

class TimerUtilMega : public TimerUtil {
public:
	TimerUtilMega()
	: callback(NULL), ticker(0)
	{
	}

	virtual ~TimerUtilMega() {}

    virtual bool attachInterrupt(Callback* callbackIn, long microsecondsIn) {
    	callback = callbackIn;
    	ticker.setPeriod((unsigned long)microsecondsIn);
    	return true;
    }

    virtual void detachInterrupt(Callback* callbackIn) {
    	callback = NULL;
    }

    virtual void hackTick() {
    	if (callback != NULL && ticker.isTime()) {
			(*callback).call();
    	}
    }

private:
    Callback* callback;
    Ticker ticker;
};

static TimerUtilMega bla = TimerUtilMega();
TimerUtil& TimerUtil::TIMERS = bla;


} /* namespace us_cownet_timers */
