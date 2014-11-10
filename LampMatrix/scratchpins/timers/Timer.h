/*
 * Timer.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <Arduino.h>

namespace timers {

/*
 * Pins 5 and 6: controlled by timer0
 * Pins 9 and 10: controlled by timer1
 * Pins 11 and 3: controlled by timer2
 *
 * On the Arduino Mega we have 6 timers and 15 PWM outputs:
 * Pins 4 and 13: controlled by timer0
 * Pins 11 and 12: controlled by timer1
 * Pins 9 and10: controlled by timer2
 * Pin 2, 3 and 5: controlled by timer 3
 * Pin 6, 7 and 8: controlled by timer 4
 * Pin 46, 45 and 44:: controlled by timer 5
 */
class Timer {
public:
	class Callback {
	public:
		virtual void loop();
	};

	virtual ~Timer();

	virtual void init() = 0;
	void addCallback(Callback* function);
	void removeCallback(Callback* function);
	virtual void setTicks(unsigned int ticks) = 0;

protected:
	Timer();
	virtual void enableCallback(bool callbackA) = 0;
	virtual void disableCallback(bool callbackA) = 0;
	Timer::Callback* callbackA;
	Timer::Callback* callbackB;
};

} /* namespace scheduler */

#endif /* TIMER_H_ */
