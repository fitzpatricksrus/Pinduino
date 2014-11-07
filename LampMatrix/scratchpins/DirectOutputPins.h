/*
 * DirectOutputPins.h
 *
 *  Created on: Oct 5, 2014
 *      Author: Dad
 */

#ifndef DIRECTOUTPUTPINS_H_
#define DIRECTOUTPUTPINS_H_

#include <Arduino.h>
#include "OutputPins.h"

namespace pins {

class DirectOutputPins : public OutputPins {
public:
	DirectOutputPins(byte pinCount, byte* pinsNumbers);
	virtual ~DirectOutputPins();
	virtual void initPins() const;
    virtual void setPinPattern(PinPattern* pattern);
    virtual void latch();

private:
    byte pinCount;
	byte* pinNumber;
	PinPattern* pattern;
};

} // namespace pins
#endif /* DIRECTOUTPUTPINS_H_ */
