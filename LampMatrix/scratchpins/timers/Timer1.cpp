/*
 * Timer1.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: Dad
 */

#include "Timer1.h"
#include <Arduino.h>

namespace timers {

//-----------------------------------------------------------------------
// Timer1 is a singleton implementation for Timer1 only.  The AVR
// library macros make it hard to abstract away registers.

const byte Timer1::prescalarValueMask = ~((1<<CS10) | (1<<CS11) | (1<<CS12));
const byte Timer1::prescalarValues[] = {
		0,
		(1<<CS10),
		(1<<CS11),
		(1<<CS10) | (1<<CS11),
		(1<<CS12),
		(1<<CS12) | (1<<CS10),
		(1<<CS12) | (1<<CS11),
		(1<<CS12) | (1<<CS11) | (1<<CS10)
};

Timer1::Timer1() {
}

Timer1::~Timer1() {
}

void Timer1::init() {
    // initialize Timer1*/
    cli();          // disable global interrupts

    TCCR1A = 0;     // set entire TCCR1A register to 0
    TCCR1B = 0;     // same for TCCR1B

    // set compare match register to desired timer count:
    OCR1A = 32000;
    // turn on CTC mode:
    TCCR1B |= (1 << WGM12);
    // Set CS10 and CS12 bits for 1024 prescaler:
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);
    // enable global interrupts:
    sei();

}

void Timer1::enableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK1 = TIMSK1 | (1 << OCIE1A);
	} else {
		TIMSK1 = TIMSK1 | (1 << OCIE1B);
	}
}

void Timer1::disableCallback(bool callbackA) {
	if (callbackA) {
		TIMSK1 = TIMSK1 & ~(1 << OCIE1A);
	} else {
		TIMSK1 = TIMSK1 & ~(1 << OCIE1B);
	}
}

void Timer1::setPrescalar(Prescalar p) {
	TCCR1B = (TCCR1B & prescalarValueMask) | prescalarValues[p];
}

void Timer1::setTicks(unsigned int desiredTicks) {
	OCR1A = desiredTicks;
	uint16_t ticksPassedThisCycle = TCNT1;
	// try to get close to the range we, keeping accumulated ticks if there are any.

	if (ticksPassedThisCycle > desiredTicks) {
		uint16_t overflow = (ticksPassedThisCycle - desiredTicks) % desiredTicks;  // handle 1 overflow, but no more
		TCNT1H = overflow >> 8;
		TCNT1L = overflow & 0xFF;
	}
}

void Timer1::loopA() {
	callbackA->loop();
}

void Timer1::loopB() {
	callbackB->loop();
}

static Timer1 timer1Instance;
Timer1& Timer1::INSTANCE = timer1Instance;

ISR(TIMER1_COMPA_vect)
{
	timer1Instance.loopA();
}

ISR(TIMER1_COMPB_vect)
{
	timer1Instance.loopB();
}

} // namespace timers

