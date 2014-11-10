/*
 * BOP.h
 *
 *  Created on: Nov 5, 2014
 *      Author: Dad
 */

#ifndef PINS_BOP_H_
#define PINS_BOP_H_


#include "AnalogOutputPins.h"
#include "OutputPins.h"
#include "../scheduler/timer.h"
#include "../scheduler/BAMTimer.h"

#define DONT_USE_MODULATED_VALUES

class BOP: public AnalogOutputPins, private scheduler::BAMTimer::Callback {
public:
	BOP(scheduler::Timer* timer, OutputPins* pins);
	virtual ~BOP();
	virtual byte getPinCount() const;
	virtual byte getPin(byte ndx) const;
	virtual void setPin(byte pinNdx, byte pinValue);
	virtual void latch();
	virtual void setEnabled(bool on);

private:
	virtual void loop(byte bit, byte mask);

	OutputPins* pins;			//the actual hardward pins
	byte* values;				//the pwm value
	scheduler::BAMTimer BAM;
#ifdef USE_MODULATED_VALUES
	void buildModulationValues();
	bool* modulatedValues[8];	//8xN booleans
#endif
};

#endif /* PINS_BOP_H_ */
