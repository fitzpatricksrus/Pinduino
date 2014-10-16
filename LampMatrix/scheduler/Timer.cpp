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
	virtual void setCallback(Timer::Callback* callback, int ticks);
};

void Timer1::setCallback(Timer::Callback* callbackIn, int ticks) {
	Timer::setCallback(callbackIn, ticks);
	getCallback()->setup();
    cli();          // disable global interrupts
    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = ticks;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable timer compare interrupt:
    TIMSK1 |= (1 << OCIE1A);
    // enable global interrupts:
    sei();
}

static Timer1 timer1Instance;
Timer Timer::TIMER1 = timer1Instance;

ISR(TIMER1_COMPA_vect)
{
	Timer::TIMER1.getCallback()->run();
}



} /* namespace Tests */
