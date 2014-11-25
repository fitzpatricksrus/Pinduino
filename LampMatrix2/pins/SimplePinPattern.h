/*
 * SimplePinPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEPINPATTERN_H_
#define SIMPLEPINPATTERN_H_

#include "../pins/PinPattern.h"

namespace pins {

class SimplePinPattern: public PinPattern {
public:
	SimplePinPattern(byte count, bool* values);
	SimplePinPattern(const SimplePinPattern& source);
	virtual ~SimplePinPattern();
	virtual PinPattern& operator=(const PinPattern& other);

	virtual byte getPinCount() const;
	virtual bool getPinValue(byte ndx) const;
	virtual bool* getPinValues() const;

	virtual void setPinValue(byte ndx, byte value);
	virtual void setPinValues(byte count, bool* values);
	virtual bool& operator[](byte ndx);

private:
	byte count;
	bool* values;
};

inline SimplePinPattern::SimplePinPattern(byte countIn, bool* valuesIn)
: count(countIn), values(valuesIn)
{
}

inline SimplePinPattern::SimplePinPattern(const SimplePinPattern& source)
: count(source.count), values(source.values)
{
}

inline SimplePinPattern::~SimplePinPattern() {
}

inline PinPattern& SimplePinPattern::operator=(const PinPattern& other) {
	if (this != &other) {
		count = other.getPinCount();
		values = other.getPinValues();
	}

	return *this;
}

inline byte SimplePinPattern::getPinCount() const {
	return count;
}

inline bool SimplePinPattern::getPinValue(byte ndx) const {
	return values[ndx];
}

inline bool* SimplePinPattern::getPinValues() const {
	return values;
}


inline void SimplePinPattern::setPinValue(byte ndx, byte value) {
	values[ndx] = value;
}

inline void SimplePinPattern::setPinValues(byte countIn, bool* valuesIn) {
	count = countIn;
	values = valuesIn;
}

inline bool& SimplePinPattern::operator [](byte ndx) {
	return values[ndx];
}

} //namespace pins

#endif /* SIMPLEPINPATTERN_H_ */
