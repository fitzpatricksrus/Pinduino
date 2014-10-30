/*
 * AnalogOutputPin.h
 *
 *  Created on: Oct 10, 2014
 *      Author: jfitzpatrick
 */

#ifndef ANALOGOUTPUTPINS_H_
#define ANALOGOUTPUTPINS_H_

#include <Arduino.h>

class AnalogOutputPins {
public:
	AnalogOutputPins();
	virtual ~AnalogOutputPins();
	virtual byte getPinCount() const = 0;
	virtual byte getPin(byte pinNdx) const = 0;
	virtual byte operator[](byte pinNdx) const;
	virtual void setPins(const byte* pinValues);
	virtual void setPin(byte pinNdx, byte pinValue) = 0;
	virtual void latch() = 0;
};

#endif /* ANALOGOUTPUTPINS_H_ */
