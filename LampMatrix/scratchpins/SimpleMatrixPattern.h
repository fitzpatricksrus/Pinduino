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
class SMatrixPattern : public MatrixPattern {
	SMatrixPattern(bool** values);
	virtual ~SMatrixPattern();

	virtual byte getRowCount() const;
	virtual byte getColCount() const;
	virtual bool* operator[](byte col) const;

	bool** values;
};

template <byte cols, byte rows>
inline byte SMatrixPattern<cols,rows>::getRowCount() const {
	return rows;
}

template <byte cols, byte rows>
inline byte SMatrixPattern<cols,rows>::getColCount() const {
	return cols;
}

template <byte cols, byte rows>
inline bool* SMatrixPattern<cols,rows>::operator[](byte col) const {
	return values[col];
}

} // namespace pins

#endif /* SCRATCHPINS_SIMPLEMATRIXPATTERN_H_ */
