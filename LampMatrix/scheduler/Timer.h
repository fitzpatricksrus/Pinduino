/*
 * Timer.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#ifndef TIMER_H_
#define TIMER_H_

namespace scheduler {

class Timer {
public:
	class Callback {
	public:
		virtual void setup() = 0;
		virtual void run() = 0;
	};

	virtual ~Timer();
	Timer::Callback* getCallback() const;
	virtual void setCallback(Timer::Callback* callback, int ticks);

	static Timer TIMER1;


protected:
	Timer();

private:
	Timer::Callback* callback;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
