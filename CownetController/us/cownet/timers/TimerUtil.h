/*
 * TimerUtil.h
 *
 *  Created on: Oct 13, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TIMERS_TIMERUTIL_H_
#define US_COWNET_TIMERS_TIMERUTIL_H_

#include "Callback.h"
#include "../utils/Map.h"
#include "PeriodicEvent.h"

namespace us_cownet_timers {

using us_cownet_utils::Map;

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

	void attachTickerCallback(Callback* c, long ticks);
	void attachTimerCallback(Callback* c, long micros);
	void detachCallback(Callback* c);
	void tick();
	void enableHackTicks(bool useHacks);
	long currentTimeMillis() const;
	unsigned long currentTimeMicros() const;
	long currentTicks() const;

	static TimerUtil& INSTANCE;

	class CallbackHandler {
	public:
		CallbackHandler();
		CallbackHandler(Callback* c, const PeriodicEvent e);

		void tick();

		Callback* c;
		PeriodicEvent e;
	};

private:
	void attachCallback(Callback* c, PeriodicEvent p);

	typedef Map<Callback*, CallbackHandler, 10> MapType;

	MapType callbackList;
	long ticks;
};

} /* namespace us_cownet_timers */

#endif /* US_COWNET_TIMERS_TIMERUTIL_H_ */

