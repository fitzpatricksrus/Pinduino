/*
 * PinPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#ifndef PINPATTERN_H_
#define PINPATTERN_H_

#include <Arduino.h>

namespace pins {

class PinPattern {
public:
	PinPattern();
	virtual ~PinPattern();

	virtual byte getPinCount() const = 0;
	virtual bool getPinValue(byte ndx) const = 0;
	virtual bool* getPinValues() const = 0;
	virtual bool operator[](byte ndx) const;
	virtual PinPattern& operator=(const PinPattern& other) = 0;
};

} // namespace pins

#endif /* PINPATTERN_H_ */
