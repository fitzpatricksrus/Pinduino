/*
 * SimpleMatrixPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#ifndef PINS_SIMPLEMATRIXPATTERN_H_
#define PINS_SIMPLEMATRIXPATTERN_H_

#include <Arduino.h>

#include "MatrixPattern.h"
#include "SimplePinPattern.h"

namespace pins {

class SimpleMatrixPattern : public MatrixPattern {
public:
	SimpleMatrixPattern(byte rows, byte cols, bool** values);
	virtual ~SimpleMatrixPattern();

	virtual byte getRowCount() const;
	virtual byte getColCount() const;
	virtual bool* operator[](byte col) const;

	byte rows;
	byte cols;
	bool** values;
};

inline byte SimpleMatrixPattern::getRowCount() const {
	return rows;
}

inline byte SimpleMatrixPattern::getColCount() const {
	return cols;
}

inline bool* SimpleMatrixPattern::operator[](byte col) const {
	return values[col];
}

} // namespace pins

#endif /* PINS_SIMPLEMATRIXPATTERN_H_ */
