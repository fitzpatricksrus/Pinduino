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
