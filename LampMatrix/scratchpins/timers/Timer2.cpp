/*
 * Timer2.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: Dad
 */

#include "Timer2.h"
#include <Arduino.h>

namespace timers {

//-----------------------------------------------------------------------
// Timer2 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.

const byte Timer2::prescalarValueMask = ~((1<<CS20) | (1<<CS21) | (1<<CS22));
const byte Timer2::prescalarValues[] = {
		0,
		(1<<CS20),
		(1<<CS21),
		(1<<CS20) | (1<<CS21),
		(1<<CS22),
		(1<<CS22) | (1<<CS20),
		(1<<CS22) | (1<<CS21),
		(1<<CS22) | (1<<CS21) | (1<<CS20)
};

Timer2::Timer2() {
}

Timer2::~Timer2() {
}

void Timer2::init() {
    // initialize Timer1*/
    cli();          // disable global interrupts

    TCCR2A = 0;     // set entire TCCR1A register to 0
    TCCR2B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR2A = 32000;
    // turn on CTC mode:
    TCCR2B |= (1 << WGM22);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR2B |= (1 << CS20);
    TCCR2B |= (1 << CS22);
    // enable global interrupts:
    sei();

}

void Timer2::enableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK2 = TIMSK2 | (1 << OCIE2A);
	} else {
		TIMSK2 = TIMSK2 | (1 << OCIE2B);
	}
}

void Timer2::disableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK2 = TIMSK2 & ~(1 << OCIE2A);
	} else {
		TIMSK2 = TIMSK2 & ~(1 << OCIE2B);
	}
}

void Timer2::setPrescalar(Prescalar p) {
	TCCR2B = (TCCR2B & prescalarValueMask) | prescalarValues[p];
}

void Timer2::setTicks(unsigned int desiredTicks) {
	OCR2A = desiredTicks;
	uint16_t ticksPassedThisCycle = TCNT2;
	// try to get close to the range we, keeping accumulated ticks if there are any.

	if (ticksPassedThisCycle > desiredTicks) {
		uint16_t overflow = (ticksPassedThisCycle - desiredTicks) % desiredTicks;  // handle 1 overflow, but no more
		TCNT2 = overflow;
	}
}

void Timer2::loopA() {
	callbackA->loop();
}

void Timer2::loopB() {
	callbackB->loop();
}

static Timer2 timer1Instance;
Timer2& Timer2::INSTANCE = timer1Instance;

ISR(TIMER2_COMPA_vect)
{
	timer1Instance.loopA();
}

ISR(TIMER2_COMPB_vect)
{
	timer1Instance.loopB();
}

} //namespace timers
