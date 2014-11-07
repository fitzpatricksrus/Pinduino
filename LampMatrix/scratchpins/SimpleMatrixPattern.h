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

namespace pins {

template <byte cols, byte rows>
class SimpleMatrixPattern : public MatrixPattern {
public:
	SimpleMatrixPattern(bool** values);
	virtual ~SimpleMatrixPattern();

	virtual byte getRowCount() const;
	virtual byte getColCount() const;
	virtual bool* operator[](byte col) const;

	bool** values;
};

} /* namespace pins */

template<byte cols, byte rows>
inline byte SimpleMatrixPattern<cols, rows>::getRowCount() const {
	return rows;
}

template<byte cols, byte rows>
inline byte SimpleMatrixPattern<cols, rows>::getColCount() const {
	return cols;
}

template<byte cols, byte rows>
inline bool* pins::SimpleMatrixPattern<cols, rows>::operator [](byte col) const {
	return values[cols][rows];
}

#endif /* SCRATCHPINS_SIMPLEMATRIXPATTERN_H_ */
