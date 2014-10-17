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

void Timer::setCallback(Timer::Callback* callbackIn, int ticks) {
	callback = callbackIn;
}

//-----------------------------------------------------------------------
class Timer1: public Timer {
public:
	Timer1();
	virtual ~Timer1();
	virtual void setCallback(Timer::Callback* callback, int ticks);
	virtual void resetTimer();
	virtual void setPrescalar(Prescalar scalar);
	virtual int getTicks() const;
	virtual void setTicks(int ticks);
};

Timer1::Timer1() {
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = 65565;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= PS1024;
    // enable timer compare interrupt:
//    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}

Timer1::~Timer1() {
}

void Timer1::setCallback(Timer::Callback* callbackIn, int ticks) {
	if (callbackIn) {
		if (callbackIn != getCallback()) {
			getCallback()->setup();
			cli();
			Timer::setCallback(callbackIn, ticks);
			// enable timer compare interrupt:
			TIMSK1 |= (1 << OCIE1A);
			sei();
		}
	} else {
	    // disable timer compare interrupt:
		cli();
		Timer::setCallback(callbackIn, ticks);
	    TIMSK1 &= ~(1 << OCIE1A);
	    sei();
	}
}

void Timer1::resetTimer() {
	TCNT1H = 0;
	TCNT1L = 0;
}

void Timer1::setPrescalar(Prescalar scalar) {
    cli();          // disable global interrupts
    TCCR1B |= (1 << CS10);
    sei();
}
int Timer1::getTicks() const {
    // set compare match register to desired timer count:
    return OCR1A;
}
void Timer1::setTicks(int ticks) {
    // set compare match register to desired timer count:
    OCR1A = ticks;
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
