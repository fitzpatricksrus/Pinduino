/*
 * PinPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#ifndef PINPATTERN_H_
#define PINPATTERN_H_

#include <Arduino.h>

class PinPattern {
public:
	PinPattern();
	virtual ~PinPattern();

	virtual byte getPinCount() const = 0;
	virtual bool getPinValue(byte ndx) const = 0;
	virtual bool operator[](byte ndx) const;
};

#endif /* PINPATTERN_H_ */
