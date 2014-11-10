/*
 * BAMTimer.h
 *
 *  Created on: Nov 5, 2014
 *      Author: Dad
 */

#ifndef SCHEDULER_BAMTIMER_H_
#define SCHEDULER_BAMTIMER_H_

#include "Timer.h"

namespace scheduler {


/*
 * A BAMTimer has 8 cycles (0 - 7), each twice as long as the last.
 * At the end of each cycle the loop() callback is called.  Timing
 * is provided exclusively by the timer passed into the constructor.
 * BAMTimer will register itself for timer callbacks and set the
 * timer ticks per interrupt.
 */
class BAMTimer : private Timer::Callback {
public:
	class Callback {
	public:
		virtual void loop(byte bit, byte mask) = 0;
	};

	BAMTimer(Timer* timer, Callback* callback);
	virtual ~BAMTimer();
	void enableCallbacks();
	void disableCallbacks();

private:
	virtual void setup();
	virtual void loop();

	byte bitInCycle;
	Timer* timer;
	Callback* callback;
};

} // end namespace scheduler

#endif /* SCHEDULER_BAMTIMER_H_ */
