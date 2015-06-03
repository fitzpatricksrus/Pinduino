/*
 * TimerUtil.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#include "TimerUtil.h"

#include <TimerThree.h>

namespace us_cownet_lamps_simple {

class DefaultTimerUtil : public TimerUtil {
public:
	DefaultTimerUtil();
	virtual ~DefaultTimerUtil();

    virtual void attachInterrupt(void (*isr)(), long microseconds=-1);
    virtual void detachInterrupt();
};

DefaultTimerUtil::DefaultTimerUtil() {
}

DefaultTimerUtil::~DefaultTimerUtil() {
	Timer3.detachInterrupt();
}

void DefaultTimerUtil::attachInterrupt(void (*isr)(), long microseconds) {
	Timer3.attachInterrupt(isr, microseconds);
}

void DefaultTimerUtil::detachInterrupt() {
	Timer3.detachInterrupt();
}



TimerUtil::TimerUtil() {

}

TimerUtil::~TimerUtil() {
}

static DefaultTimerUtil INSTANCE = DefaultTimerUtil();
TimerUtil& TimerUtil::DEFAULT_TIMER = INSTANCE;

} /* namespace pins */
