/*
 * MatrixPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#ifndef PINS_MATRIXPATTERN_H_
#define PINS_MATRIXPATTERN_H_

#include <Arduino.h>

#include "PinPattern.h"

namespace pins {

class MatrixPattern {
public:
	MatrixPattern();
	virtual ~MatrixPattern();

	virtual byte getRowCount() const = 0;
	virtual byte getColCount() const = 0;
	virtual bool* operator[](byte col) const = 0;
	bool getPinValue(byte col, byte row) const;
};

inline bool MatrixPattern::getPinValue(byte col, byte row) const {
	return (*this)[col][row];
}

} /* namespace pins */

#endif /* PINS_MATRIXPATTERN_H_ */
