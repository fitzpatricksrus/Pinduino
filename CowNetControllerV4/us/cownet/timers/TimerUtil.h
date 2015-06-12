/*
 * TimerUtil.h
 *
 *  Created on: Jun 4, 2015
 *      Author: jfitzpatrick
 */

#ifndef TIMERUTIL_H_
#define TIMERUTIL_H_

#include "Callback.h"

#include "Ticker.h"

namespace us_cownet_timers {

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

    virtual bool attachInterrupt(Callback* callback, long microseconds=-1);
    virtual void detachInterrupt(Callback* callback);

    virtual void hackTick();
    virtual void hackTime(long timeInMicros);

    virtual long currentTimeMillis();
    virtual long currentTimeMicros();

    static TimerUtil& INSTANCE;
    static const long REAL_TICKS = -1;

private:
    Callback* callback;
    Ticker ticker;
    long hackMicros;
};

} /* namespace us_cownet_timers */

#endif /* TIMERUTIL_H_ */
