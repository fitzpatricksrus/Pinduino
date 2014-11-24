/*
 * BAMOutputPins.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#ifndef BAMOUTPUTPINS_H_
#define BAMOUTPUTPINS_H_

#include "AnalogOutputPins.h"
#include "OutputPins.h"
#include "../scheduler/timer.h"
#include "../scheduler/BAMTimer.h"

#define DONT_USE_MODULATED_VALUES

class BAMOutputPins: public AnalogOutputPins, private scheduler::BAMTimer::Callback {
public:
	BAMOutputPins(scheduler::Timer* timer, OutputPins* pins);
	virtual ~BAMOutputPins();
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


#endif /* BAMOUTPUTPINS_H_ */
