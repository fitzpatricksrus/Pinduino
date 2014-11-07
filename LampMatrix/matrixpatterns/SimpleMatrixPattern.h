/*
 * ConcreteMatrixPattern.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Dad
 */

#ifndef SIMPLEMATRIXPATTERN_H_
#define SIMPLEMATRIXPATTERN_H_

#include "MatrixPattern.h"

namespace matrixpatterns {

template<byte COLS, byte ROWS>
class SimpleMatrixPattern: public MatrixPattern {
public:
	typedef byte ValueArray[COLS][ROWS];

	SimpleMatrixPattern(ValueArray& values, byte pwmSteps);
	virtual ~SimpleMatrixPattern();
	virtual byte getPWMSteps() const;
	virtual byte getRowCount() const;
	virtual byte getColumnCount() const;
	virtual byte getValue(byte row, byte column) const;
	virtual byte const* operator[](byte columnIndex) const;
	virtual byte* operator[](byte columnIndex);

protected:
	byte pwmSteps;
	ValueArray& values;
};

template<byte COLS, byte ROWS>
SimpleMatrixPattern<COLS, ROWS>::SimpleMatrixPattern(
		ValueArray& valuesIn, byte pwnStepsIn) :
		pwmSteps(pwnStepsIn), values(valuesIn) {
}

template<byte COLS, byte ROWS>
SimpleMatrixPattern<COLS, ROWS>::~SimpleMatrixPattern() {
}

template<byte COLS, byte ROWS>
byte SimpleMatrixPattern<COLS, ROWS>::getPWMSteps() const {
	return pwmSteps;
}

template<byte COLS, byte ROWS>
byte SimpleMatrixPattern<COLS, ROWS>::getRowCount() const {
	return ROWS;
}

template<byte COLS, byte ROWS>
byte SimpleMatrixPattern<COLS, ROWS>::getColumnCount() const {
	return COLS;
}

template<byte COLS, byte ROWS>
byte SimpleMatrixPattern<COLS, ROWS>::getValue(byte row, byte column) const {
	return values[column][row];
}

template<byte COLS, byte ROWS>
byte const* SimpleMatrixPattern<COLS, ROWS>::operator[](
		byte columnIndex) const {
	return values[columnIndex];
}

template<byte COLS, byte ROWS>
byte* SimpleMatrixPattern<COLS, ROWS>::operator[](byte columnIndex) {
	return values[columnIndex];
}

} // namespace matrixpatterns

#endif /* CONCRETEMATRIXPATTERN_H_ */
