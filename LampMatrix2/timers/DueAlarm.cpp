/*
 * DueAlarm.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: Dad
 */

#include "DueAlarm.h"

namespace timers {

#ifdef __arm__

/*
  DueAlarm.cpp - Implementation of Timers defined on DueAlarm.h
  For instructions, go to https://github.com/ivanseidel/DueAlarm

  Created by Ivan Seidel Gomes, March, 2013.
  Modified by Philipp Klaus, June 2013.
  Thanks to stimmer (from Arduino forum), for coding the "timer soul" (Register stuff)
  Released into the public domain.
*/

// Store timer configuration (static, as it's fixed for every object)
static const timers::DueAlarm::Timer Timers[NUM_TIMERS] = {
	{TC0,0,TC0_IRQn},
	{TC0,1,TC1_IRQn},
	{TC0,2,TC2_IRQn},
	{TC1,0,TC3_IRQn},
	{TC1,1,TC4_IRQn},
	{TC1,2,TC5_IRQn},
	{TC2,0,TC6_IRQn},
	{TC2,1,TC7_IRQn},
	{TC2,2,TC8_IRQn},
};

DueAlarm::DueAlarm(unsigned short _timer)
: timer(_timer), frequency(-1)
{
}

void DueAlarm::start() {
	if(frequency <= 0)
		setFrequency(1);

	NVIC_ClearPendingIRQ(Timers[timer].irq);
	NVIC_EnableIRQ(Timers[timer].irq);

	TC_Start(Timers[timer].tc, Timers[timer].channel);
}

void DueAlarm::stop() {
	/*
		Stop the timer
	*/

	NVIC_DisableIRQ(Timers[timer].irq);

	TC_Stop(Timers[timer].tc, Timers[timer].channel);
}

uint8_t DueAlarm::bestClock(double frequency, uint32_t& retRC){
	/*
		Pick the best Clock, thanks to Ogle Basil Hall!

		Timer		Definition
		TIMER_CLOCK1	MCK /  2
		TIMER_CLOCK2	MCK /  8
		TIMER_CLOCK3	MCK / 32
		TIMER_CLOCK4	MCK /128
	*/
	const struct {
		uint8_t flag;
		uint8_t divisor;
	} clockConfig[] = {
		{ TC_CMR_TCCLKS_TIMER_CLOCK1,   2 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK2,   8 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK3,  32 },
		{ TC_CMR_TCCLKS_TIMER_CLOCK4, 128 }
	};
	float ticks;
	float error;
	int clkId = 3;
	int bestClock = 3;
	float bestError = 1.0;
	do
	{
		ticks = (float) VARIANT_MCK / frequency / (float) clockConfig[clkId].divisor;
		error = abs(ticks - round(ticks));
		if (error < bestError)
		{
			bestClock = clkId;
			bestError = error;
		}
	} while (clkId-- > 0);
	ticks = (float) VARIANT_MCK / frequency / (float) clockConfig[bestClock].divisor;
	retRC = (uint32_t) round(ticks);
	return clockConfig[bestClock].flag;
}


void DueAlarm::setFrequency(double frequencyIn){
	// Set the timer frequency (in Hz)

	// Prevent negative frequencies
	if (frequencyIn <= 0) {
		frequencyIn = 1;
	}

	// Remember the frequency
	frequency = frequencyIn;

	// Get current timer configuration
	Timer t = Timers[timer];

	uint32_t rc = 0;
	uint8_t clock;

	// Tell the Power Management Controller to disable
	// the write protection of the (Timer/Counter) registers:
	pmc_set_writeprotect(false);

	// Enable clock for the timer
	pmc_enable_periph_clk((uint32_t)t.irq);

	// Find the best clock for the wanted frequency
	clock = bestClock(frequency, rc);

	// Set up the Timer in waveform mode which creates a PWM
	// in UP mode with automatic trigger on RC Compare
	// and sets it up with the determined internal clock as clock input.
	TC_Configure(t.tc, t.channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | clock);
	// Reset counter and fire interrupt when RC value is matched:
	TC_SetRC(t.tc, t.channel, rc);
	// Enable the RC Compare Interrupt...
	t.tc->TC_CHANNEL[t.channel].TC_IER=TC_IER_CPCS;
	// ... and disable all others.
	t.tc->TC_CHANNEL[t.channel].TC_IDR=~TC_IER_CPCS;
}

void DueAlarm::setPeriod(unsigned long microseconds){
	/*
		Set the period of the timer (in microseconds)
	*/

	// Convert period in microseconds to frequency in Hz
	double frequency = 1000000.0 / microseconds;
	setFrequency(frequency);
}

double DueAlarm::getFrequency() const {
	return frequency;
}

long DueAlarm::getPeriod() const {
	return 1.0/getFrequency()*1000000;
}


/*
	Implementation of the timer callbacks defined in
	arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/sam3xa/include/sam3x8e.h
*/
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
void TC0_Handler() {
	TC_GetStatus(TC0, 0);
	DueAlarm::timer0.doCallback();
}
#endif
void TC1_Handler() {
	TC_GetStatus(TC0, 1);
	DueAlarm::timer1.doCallback();
}
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
void TC2_Handler() {
	TC_GetStatus(TC0, 2);
	DueAlarm::timer2.doCallback();
}
void TC3_Handler() {
	TC_GetStatus(TC1, 0);
	DueAlarm::timer3.doCallback();
}
void TC4_Handler() {
	TC_GetStatus(TC1, 1);
	DueAlarm::timer4.doCallback();
}
void TC5_Handler() {
	TC_GetStatus(TC1, 2);
	DueAlarm::timer5.doCallback();
}
#endif
void TC6_Handler() {
	TC_GetStatus(TC2, 0);
	DueAlarm::timer6.doCallback();
}
void TC7_Handler() {
	TC_GetStatus(TC2, 1);
	DueAlarm::timer7.doCallback();
}
void TC8_Handler() {
	TC_GetStatus(TC2, 2);
	DueAlarm::timer8.doCallback();
}

/*
	Initializing all timers, so you can use them like this: Timer0.start();
*/
static DueAlarm Timer(0);
static DueAlarm Timer1(1);
// Fix for compatibility with Servo library
#ifndef USING_SERVO_LIB
static DueAlarm Timer0(0);
static DueAlarm Timer2(2);
static DueAlarm Timer3(3);
static DueAlarm Timer4(4);
static DueAlarm Timer5(5);
#endif
static DueAlarm Timer6(6);
static DueAlarm Timer7(7);
static DueAlarm Timer8(8);

DueAlarm& DueAlarm::timer0 = Timer0;
DueAlarm& DueAlarm::timer1 = Timer1;
DueAlarm& DueAlarm::timer2 = Timer2;
DueAlarm& DueAlarm::timer3 = Timer3;
DueAlarm& DueAlarm::timer4 = Timer4;
DueAlarm& DueAlarm::timer5 = Timer5;
DueAlarm& DueAlarm::timer6 = Timer6;
DueAlarm& DueAlarm::timer7 = Timer7;
DueAlarm& DueAlarm::timer8 = Timer8;


#endif

} /* namespace timers */
