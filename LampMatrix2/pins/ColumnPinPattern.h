/*
 * ColumnPinPattern.h
 *
 *  Created on: Nov 25, 2014
 *      Author: Dad
 */

#ifndef PINS_COLUMNPINPATTERN_H_
#define PINS_COLUMNPINPATTERN_H_

#include "PinPattern.h"

namespace pins {

class ColumnPinPattern: public PinPattern {
public:
	ColumnPinPattern();
	ColumnPinPattern(byte count);
	virtual ~ColumnPinPattern();

	virtual byte getPinCount() const;
	virtual bool getPinValue(byte ndx) const;
//	virtual bool* getPinValues() const = 0;

	ColumnPinPattern& setColumnCount(byte count);
	byte getCurrentColumn() const;
	ColumnPinPattern& setCurrentColumn(byte col);
	ColumnPinPattern& operator++();
	operator byte();

private:
	byte col;
	byte count;
};


inline ColumnPinPattern::ColumnPinPattern()
: col(0), count(0)
{
}

inline ColumnPinPattern::ColumnPinPattern(byte countIn)
: col(0), count(countIn)
{
}

inline ColumnPinPattern::~ColumnPinPattern() {
}

inline byte ColumnPinPattern::getPinCount() const {
	return count;
}

inline bool ColumnPinPattern::getPinValue(byte ndx) const {
	return ndx == col;
}

inline ColumnPinPattern& ColumnPinPattern::setColumnCount(byte countIn) {
	count = countIn;
	return *this;
}

inline byte ColumnPinPattern::getCurrentColumn() const {
	return col;
}

inline ColumnPinPattern& ColumnPinPattern::setCurrentColumn(byte colIn) {
	col = colIn;
	return *this;
}

inline ColumnPinPattern& ColumnPinPattern::operator++() {
	col = (col + 1) % count;
	return *this;
}

inline ColumnPinPattern::operator byte() {
	return col;
}


} /* namespace pins */

#endif /* PINS_COLUMNPINPATTERN_H_ */
