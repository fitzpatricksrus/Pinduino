/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <Arduino.h>

namespace us_cownet_timers {

TimerUtil::TimerUtil() {
}

TimerUtil::~TimerUtil() {
}

class TimerUtilMega : public TimerUtil {
public:
	TimerUtilMega()
	: callback(NULL), microseconds(0), lastTick(0)
	{
	}

	virtual ~TimerUtilMega() {}

    virtual bool attachInterrupt(Callback* callbackIn, long microsecondsIn) {
    	callback = callbackIn;
    	microseconds = microsecondsIn;
    	return true;
    }

    virtual void detachInterrupt(Callback* callbackIn) {
    	callback = NULL;
    }

    virtual void hackTick() {
    	if (micros() - lastTick > microseconds) {
    		lastTick = micros();
    		if (callback != NULL) {
    			(*callback).call();
    		}
    	}
    }

private:
    Callback* callback;
    long microseconds;
    long lastTick;
};

static TimerUtilMega bla = TimerUtilMega();
TimerUtil& TimerUtil::TIMERS = bla;


} /* namespace us_cownet_timers */
