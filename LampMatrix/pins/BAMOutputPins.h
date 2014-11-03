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

class BAMOutputPins: public AnalogOutputPins, private scheduler::Timer::Callback {
public:
	BAMOutputPins(scheduler::Timer* timer, OutputPins* pins);
	virtual ~BAMOutputPins();
	virtual byte getPinCount() const;
	virtual byte getPin(byte ndx) const;
	virtual void setPin(byte pinNdx, byte pinValue);
	virtual void latch();

private:
	virtual void setup();
	virtual void loop();

	OutputPins* pins;
	byte* values;
	byte bitInCycle;
	scheduler::Timer* timer;
};

#endif /* BAMOUTPUTPINS_H_ */
