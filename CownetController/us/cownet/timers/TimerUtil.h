/*
 * TimerUtil.h
 *
 *  Created on: Oct 13, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_TIMERS_TIMERUTIL_H_
#define US_COWNET_TIMERS_TIMERUTIL_H_

namespace us_cownet_timers {

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

private:
	HashMap<Callback, CallbackHandler> callbackList;
	long ticks;
};

} /* namespace us_cownet_timers */

#endif /* US_COWNET_TIMERS_TIMERUTIL_H_ */
