/*
 * UnoAlarm.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: Dad
 */

#include "UnoAlarm.h"
#include "TimerVectors.h"

namespace timers {

static const double systemFrequency = 16.0 * 1000000.0;

static void initTimers();

UnoAlarm::UnoAlarm(const PrescalarDef* scalarsIn, bool isTimerAIn)
: scalars(scalarsIn), isTimerA(isTimerAIn)
{
	initTimers();
}

UnoAlarm::~UnoAlarm() {
}

void UnoAlarm::setFrequency(double frequencyHz) {
	int f = 1;
	// if we need a frequency >= system frequency, use scalar of 1
	do {
		double interuptFrequency = (systemFrequency / scalars[f].scalar);
		if (frequencyHz < interuptFrequency) {
			// so, now that we have more ticks than required, use counts to scale back further
			break;
		}
	} while (scalars[f].scalar != 1);
	double interuptFrequency = (systemFrequency / scalars[f].scalar);
	unsigned int ticks = interuptFrequency / frequencyHz;
	if (ticks > scalars[0].scalar) {
		ticks = scalars[0].scalar;
	}
	cli();
	setScalar(scalars[0].mask, scalars[f].mask);
	setTicks(ticks);
	sei();
}

void UnoAlarm::setPeriod(unsigned long periodUs) {
	// Set the period of the timer (in microseconds)
	// Convert period in microseconds to frequency in Hz
	double frequency = 1000000.0 / periodUs;
	setFrequency(frequency);
}

class UnoAlarm1 : public UnoAlarm {
public:
	UnoAlarm1(const PrescalarDef scalarsIn[], bool isTimerAIn)
		: UnoAlarm(scalarsIn, isTimerAIn) {}
	virtual void start();
	virtual void stop();
	virtual void setTicks(int ticks);
	virtual void setScalar(byte andMask, byte orMask);
};

void UnoAlarm1::start() {
	TIMSK1 = TIMSK1 | (1 << ((isTimerA) ? OCIE1A : OCIE1B));
}
void UnoAlarm1::stop() {
	TIMSK1 = TIMSK1 & ~(1 << (isTimerA ? OCIE1A : OCIE1B));
}
void UnoAlarm1::setTicks(int ticks) {
	if (isTimerA) {
		OCR1A = ticks;
	} else {
		OCR1B = ticks;
	}
}
void UnoAlarm1::setScalar(byte andMask, byte orMask) {
	TCCR1B = (TCCR1B & andMask) | orMask;
}

class UnoAlarm2 : public UnoAlarm {
public:
	UnoAlarm2(const PrescalarDef scalarsIn[], bool isTimerAIn)
	: UnoAlarm(scalarsIn, isTimerAIn) {}
	virtual void start();
	virtual void stop();
	virtual void setTicks(int ticks);
	virtual void setScalar(byte andMask, byte orMask);
};

void UnoAlarm2::start() {
	TIMSK2 = TIMSK2 | (1 << (isTimerA ? OCIE2A : OCIE2B));
}
void UnoAlarm2::stop() {
	TIMSK2 = TIMSK2 & ~(1 << (isTimerA ? OCIE2A : OCIE2B));
}
void UnoAlarm2::setTicks(int ticks) {
	if (isTimerA) {
		OCR2A = ticks;
	} else {
		OCR2B = ticks;
	}
}
void UnoAlarm2::setScalar(byte andMask, byte orMask) {
	TCCR2B = (TCCR2B & andMask) | orMask;
}

static const UnoAlarm::PrescalarDef prescalarValues1[] = {
		{ 65535, ~((1u << CS10) | (1u << CS11) | (1u << CS12)) },
		{ 1024, (1<<CS12) | (1<<CS10) },
		{ 256, (1<<CS12) },
		{ 64, (1<<CS10) | (1<<CS11) },
		{ 8, (1<<CS11) },
		{ 1, (1<<CS10) }
};
static UnoAlarm1 alarm1aInstance(prescalarValues1, true);
static UnoAlarm1 alarm1bInstance(prescalarValues1, false);
Alarm& UnoAlarm::alarm1a = alarm1aInstance;	//16 bit timer
Alarm& UnoAlarm::alarm1b = alarm1bInstance;

static void Callback1A() {
	alarm1aInstance.doCallback();
}

static void Callback1B() {
	alarm1bInstance.doCallback();
}

static const UnoAlarm::PrescalarDef prescalarValues2[] = {
		{ 255, ~((1<<CS20) | (1<<CS21) | (1<<CS22)) },
		{1024, (1<<CS22) | (1<<CS21) | (1<<CS20) },
		{ 256, (1<<CS22) | (1<<CS21) },
		{ 128, (1<<CS22) | (1<<CS20) },
		{  64, (1<<CS22) },
		{  32, (1<<CS20) | (1<<CS21) },
		{   8, (1<<CS21) },
		{   1, (1<<CS20) }
};
static UnoAlarm2 alarm2aInstance(prescalarValues2, true);
static UnoAlarm2 alarm2bInstance(prescalarValues2, false);
Alarm& UnoAlarm::alarm2a = alarm2aInstance;	//8 bit timer
Alarm& UnoAlarm::alarm2b = alarm2bInstance;
static void Callback2A() {
	alarm2aInstance.doCallback();
}
static void Callback2B() {
	alarm2bInstance.doCallback();
}

static bool unoTimersNeedInit = true;
static void initTimers() {
	if (unoTimersNeedInit) {
	    cli();          // disable global interrupts

	    TimerVectors::timer1aVector.attachInterrupt(&Callback1A);
	    TimerVectors::timer1bVector.attachInterrupt(&Callback1B);
	    TimerVectors::timer2aVector.attachInterrupt(&Callback2A);
	    TimerVectors::timer2bVector.attachInterrupt(&Callback2B);

	    //init timer1
	    TCCR1A = 0;     // set entire TCCR1A register to 0
	    TCCR1B = 0;     // same for TCCR1B
	    // set compare match register to desired timer count:
	    OCR1A = 32000;
	    OCR1B = 32000;
	    // turn on CTC mode:
	    TCCR1B |= (1 << WGM12);
	    // Set CS10 and CS12 bits for 1024 prescaler:
	    TCCR1B |= (1 << CS10);
	    TCCR1B |= (1 << CS12);

	    //init timer2
	    TCCR2A = 0;     // set entire TCCR1A register to 0
	    TCCR2B = 0;     // same for TCCR1B
	    // set compare match register to desired timer count:
	    OCR2A = 255;
	    OCR2B = 255;
	    // turn on CTC mode:
	    TCCR2B |= (1 << WGM22);
	    // Set CS10 and CS12 bits for 1024 prescaler:
	    TCCR2B |= (1 << CS20);
	    TCCR2B |= (1 << CS22);

	    unoTimersNeedInit = false;
	    // enable global interrupts:
	    sei();
	}
}

} /* namespace timers */
