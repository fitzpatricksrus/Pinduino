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

class BAMOutputPins: public AnalogOutputPins {
public:
	enum MaxAnalogValue {
		MAX1, MAX3, MAX7, MAX15, MAX31, MAX63, MAX127, MAX255 };

	BAMOutputPins(unsigned int dutyCycleMicros, MaxAnalogValue maxValue, OutputPins* pins);
	virtual ~BAMOutputPins();
	virtual byte getPinCount() const;
	virtual byte getPin(byte) const;
	virtual void setPin(byte pinNdx, byte pinValue);
	virtual void latch(unsigned long now);
private:
	OutputPins* pins;
	byte* values;
	MaxAnalogValue maxValue;
	unsigned int dutyCycleMicros;
};

#endif /* BAMOUTPUTPINS_H_ */
