/*
 * SimplePinPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEPINPATTERN_H_
#define SIMPLEPINPATTERN_H_

#include "PinPattern.h"

namespace pins {

template<byte count>
class SimplePinPattern: public PinPattern {
public:
	SimplePinPattern(byte* values);
	virtual ~SimplePinPattern();

	virtual byte getPinCount() const;
	virtual bool getPinValue(byte ndx) const;

	virtual void setPinValue(byte ndx, byte value);
	virtual byte& operator[](byte ndx);

private:
	byte* values;
};

template<byte count>
inline SimplePinPattern<count>::SimplePinPattern(byte* valuesIn)
: values(valuesIn)
{
}

template<byte count>
inline SimplePinPattern<count>::~SimplePinPattern() {
}

template<byte count>
inline byte SimplePinPattern<count>::getPinCount() const {
	return count;
}

template<byte count>
inline bool SimplePinPattern<count>::getPinValue(byte ndx) const {
	return values[ndx];
}

template<byte count>
inline void SimplePinPattern<count>::setPinValue(byte ndx, byte value) {
	values[ndx] = value;
}

template<byte count>
inline byte& SimplePinPattern<count>::operator [](byte ndx) {
	return values[ndx];
}

} //namespace pins

#endif /* SIMPLEPINPATTERN_H_ */
