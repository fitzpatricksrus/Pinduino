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

	virtual void attachTickerCallback(Callback* callback, unsigned long ticks);
	virtual void detachTickerCallback(Callback* callback);

	virtual void attachTimerCallback(Callback* callback, unsigned long micros);
	virtual void detachTimerCallback(Callback* callback);

	virtual void tick();
	virtual void enableHackTicks(bool userHacks);
	virtual unsigned long currentTimeMillis();
	virtual unsigned long currentTimeMicros();
	virtual unsigned long currentTicks();

    static TimerUtil& INSTANCE;
    static const long REAL_TICKS = -1;

private:
    Callback* callback;
    Ticker ticker;
    long hackMicros;
};

} /* namespace us_cownet_timers */

#endif /* TIMERUTIL_H_ */
