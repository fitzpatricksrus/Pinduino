/*
 * Timer.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>

namespace scheduler {

class Timer {
public:
	class Callback {
	public:
		virtual void setup() = 0;
		virtual void run() = 0;
	};
	enum Prescalar { PS1 = (1 << CS10), PS8 = (1 << CS11), PS64 = (1 << CS10) | (1 << CS11),
		PS256 = (1 << CS12), PS1024 = (1 << CS10) | (1 << CS12) };

	virtual ~Timer();
	Timer::Callback* getCallback() const;
	virtual void setCallback(Timer::Callback* callback, int ticks);
	virtual void resetTimer() = 0;
	virtual void setPrescalar(Prescalar scalar) = 0;
	virtual int getTicks() const = 0;
	virtual void setTicks(int ticks) = 0;

	static Timer& TIMER1;


protected:
	Timer();

private:
	Timer::Callback* callback;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
