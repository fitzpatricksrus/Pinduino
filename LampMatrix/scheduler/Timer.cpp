/*
 * Timer.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: Dad
 */

#include "Timer.h"

#include <Arduino.h>

namespace scheduler {

Timer::Timer()
	: callback(0)
{
}

Timer::~Timer() {
}

Timer::Callback* Timer::getCallback() const {
	return callback;
}

void Timer::setCallback(Timer::Callback* callbackIn, Prescalar p, int ticks) {
	if (callbackIn) {
		if (callbackIn != getCallback()) {
			getCallback()->setup();
			cli();
			callback = callbackIn;
			setPrescalar(p);
			setTicks(p);
			// enable timer compare interrupt:
			enableCallbacks();
			sei();
		}
	} else {
	    // disable timer compare interrupt:
		cli();
		disableCallBacks();
		callback = callbackIn;
	    sei();
	}
}

//-----------------------------------------------------------------------
class Timer1: public Timer {
public:
	Timer1();
	virtual ~Timer1();
	virtual void resetTimer();
	virtual void enableCallbacks();
	virtual void disableCallBacks();
	virtual void setPrescalar(Prescalar p);
	virtual void setTicks(int ticks);
};

Timer1::Timer1() {
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    disableCallBacks();
    setTicks(65535);
    setPrescalar(TIMER_OFF);
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // enable global interrupts:
    sei();
}

Timer1::~Timer1() {
}

void Timer1::resetTimer() {
	TCNT1H = 0;
	TCNT1L = 0;
}

void Timer1::enableCallbacks() {
	TIMSK1 |= (1 << OCIE1A);
}

void Timer1::disableCallBacks() {
    TIMSK1 &= ~(1 << OCIE1A);
}

static byte prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
static byte prescalarValues[] = {
		0,
		(1<<CS10),
		(1<<CS11),
		(1<<CS10) | (1<<CS11),
		(1<<CS12),
		(1<<CS12) | (1<<CS10),
		(1<<CS12) | (1<<CS11),
		(1<<CS12) | (1<<CS11) | (1<<CS10)
};

void Timer1::setPrescalar(Prescalar p) {
	TCCR1B = (TCCR1B & prescalarValueMask) | prescalarValues[p];
}
void Timer1::setTicks(int ticks) {
	cli();
	OCR1A = ticks;
	resetTimer();
	sei();
}

static Timer1 timer1Instance;
Timer& Timer::TIMER1 = timer1Instance;

ISR(TIMER1_COMPA_vect)
{
	Timer::Callback* timer = Timer::TIMER1.getCallback();
	if (timer) {
		Timer::TIMER1.getCallback()->run();
	}
}



} /* namespace Tests */
