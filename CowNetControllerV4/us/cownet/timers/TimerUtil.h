/*
 * TimerUtil.h
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#ifndef TIMERUTIL_H_
#define TIMERUTIL_H_

#include "Callback.h"

namespace us_cownet_timers {

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

    virtual bool attachInterrupt(Callback* callback, long microseconds=-1) = 0;
    virtual void detachInterrupt(Callback* callback) = 0;

    virtual void hackTick() = 0;

    static TimerUtil& TIMERS;
};

} /* namespace us_cownet_timers */

#endif /* TIMERUTIL_H_ */
