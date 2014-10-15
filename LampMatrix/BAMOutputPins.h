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
#include "scheduler/scheduler.h"

class BAMOutputPins: public AnalogOutputPins {
public:
	BAMOutputPins(unsigned int dutyCycleMicros, OutputPins* pins);
	virtual ~BAMOutputPins();
	virtual byte getPinCount() const;
	virtual byte getPin(byte) const;
	virtual void setPin(byte pinNdx, byte pinValue);
	virtual void latch();
private:
	OutputPins* pins;
	byte* values;
	unsigned int dutyCycleMicros[8];
	byte bitInCycle;
};

#endif /* BAMOUTPUTPINS_H_ */
