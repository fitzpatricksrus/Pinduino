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
#include "Timer.h"
#include "PeriodicEvent.h"

namespace us_cownet_timers {

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

	virtual void attachTickerCallback(Callback* callback, unsigned long ticks);
	virtual void attachTimerCallback(Callback* callback, unsigned long micros);
	virtual void detachCallback(Callback* callback);

	virtual void tick();
	virtual void enableHackTicks(bool userHacks);
	virtual unsigned long currentTimeMillis();
	virtual unsigned long currentTimeMicros();
	virtual unsigned long currentTicks();

    static TimerUtil& INSTANCE;
    static const long REAL_TICKS = -1;

private:
    class CallbackEntry {
    public:
    	CallbackEntry();
    	CallbackEntry(Callback* c, bool isTicker, unsigned long period);
    	CallbackEntry(const CallbackEntry& other);
    	void tick();

    	Callback* callback;
    	PeriodicEvent event;
    };

    static const int MAX_CALLBACKS = 20;

    CallbackEntry callbackList[MAX_CALLBACKS];
    int size;
	unsigned long ticks;
	bool useHackTicks;
};

} /* namespace us_cownet_timers */

#endif /* TIMERUTIL_H_ */
