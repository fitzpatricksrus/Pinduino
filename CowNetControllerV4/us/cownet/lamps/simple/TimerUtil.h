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

    static void attachInterrupt(void (*isr)(), long microseconds=-1);
    static void detachInterrupt();

};

} /* namespace pins */

#endif /* TIMERUTIL_H_ */
