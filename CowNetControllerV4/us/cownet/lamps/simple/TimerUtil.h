/*
 * TimerUtil.h
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef TIMERUTIL_H_
#define TIMERUTIL_H_

namespace us_cownet_lamps_simple {

class TimerUtil {
public:
	TimerUtil();
	virtual ~TimerUtil();

    virtual void attachInterrupt(void (*isr)(), long microseconds=-1) = 0;
    virtual void detachInterrupt() = 0;

    static TimerUtil& DEFAULT_TIMER;
};

} /* namespace pins */

#endif /* TIMERUTIL_H_ */
