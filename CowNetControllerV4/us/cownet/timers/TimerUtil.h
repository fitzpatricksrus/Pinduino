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
#include "../util/ArrayList.h"
#include "../util/HashMap.h"

namespace us_cownet_timers {

using us_cownet_util::ArrayList;
using us_cownet_util::HashMap;

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
    static const int MAX_CALLBACKS = 20;

    class CallbackHandler {
	public:
		CallbackHandler();
		void invokeCallbacks();
		void addCallback(Callback* c);
		void removeCallback(Callback* c);
		bool isEmpty();
	private:
		ArrayList<Callback, MAX_CALLBACKS> callbacks;
	};

    HashMap<Ticker*, CallbackHandler, MAX_CALLBACKS> tickerCallbackList;
    HashMap<unsigned long, Ticker, MAX_CALLBACKS> tickers;

    HashMap<Timer*, CallbackHandler, MAX_CALLBACKS> timerCallbackList;
    HashMap<unsigned long, Timer, MAX_CALLBACKS> timers;

	unsigned long ticks;
	bool useHackTicks;
};

} /* namespace us_cownet_timers */

#endif /* TIMERUTIL_H_ */
