/*
 * MatrixPattern.h
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#ifndef SCRATCHPINS_MATRIXPATTERN_H_
#define SCRATCHPINS_MATRIXPATTERN_H_

#include <Arduino.h>

namespace pins {

class MatrixPattern {
public:
	MatrixPattern();
	virtual ~MatrixPattern();

	virtual byte getRowCount() const = 0;
	virtual byte getColCount() const = 0;
	virtual bool* operator[](byte col) const = 0;
	virtual bool getPinValue(byte col, byte row) const;
};

} /* namespace pins */

#endif /* SCRATCHPINS_MATRIXPATTERN_H_ */
