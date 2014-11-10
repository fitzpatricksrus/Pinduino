/*
 * SimpleMatrixPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_SIMPLEMATRIXPATTERN_H_
#define SCRATCHPINS_SIMPLEMATRIXPATTERN_H_

#include <Arduino.h>
#include "MatrixPattern.h"
#include "SimplePinPattern.h"

namespace pins {

class SMatrixPattern : public MatrixPattern {
public:
	SMatrixPattern(byte rows, byte cols, bool** values);
	virtual ~SMatrixPattern();

	virtual byte getRowCount() const;
	virtual byte getColCount() const;
	virtual bool* operator[](byte col) const;
	virtual void getColumnPattern(byte col, PinPattern& pattern) const;

	byte rows;
	byte cols;
	bool** values;
};

inline byte SMatrixPattern::getRowCount() const {
	return rows;
}

inline byte SMatrixPattern::getColCount() const {
	return cols;
}

inline bool* SMatrixPattern::operator[](byte col) const {
	return values[col];
}

inline void SMatrixPattern::getColumnPattern(byte col, PinPattern& pattern) const {
	pattern = SimplePinPattern(rows, values[col]);
}


} // namespace pins

#endif /* SCRATCHPINS_SIMPLEMATRIXPATTERN_H_ */
