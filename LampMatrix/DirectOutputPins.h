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

class DirectOutputPins : public OutputPins {
public:
	DirectOutputPins();
	DirectOutputPins(byte pinCount, byte pins[]);
	DirectOutputPins(const DirectOutputPins& source);
	virtual ~DirectOutputPins();
	virtual DirectOutputPins& operator=(const DirectOutputPins& other);
	virtual void initPins() const;
	virtual bool getPin(byte pinNdx) const;
	virtual void setPin(byte pinNdx, bool value);
	virtual byte getPinCount() const;
	virtual void latch();

private:
	byte* pinNumber;
    bool* pinValue;
    byte pinCount;
};

inline byte DirectOutputPins::getPinCount() const {
    return pinCount;
}

inline bool DirectOutputPins::getPin(byte pinNdx) const {
	return pinValue[pinNdx];
}

#endif /* DIRECTOUTPUTPINS_H_ */
