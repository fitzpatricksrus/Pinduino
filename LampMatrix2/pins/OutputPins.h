/*
 * OutputPins.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#ifndef OUTPUTPINS_H_
#define OUTPUTPINS_H_

#include <Arduino.h>

#include "../pins/PinPattern.h"

namespace pins {

/*
 * A set of pins with particular values.  Pin values
 * are cached and only sent to the output pins
 * when latch() is called.  Subclasses should optimize
 * for latch() speed rather than pin update speed.
 */
class OutputPins {
public:
	OutputPins();
	virtual ~OutputPins();
	virtual void initPins() const = 0;
    virtual void setPinPattern(PinPattern* pattern) = 0;
    virtual void latch() = 0;
};

} //namespace pins

#endif /* OUTPUTPINS_H_ */
