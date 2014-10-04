/*
 * ConcreteMatrixPattern.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Dad
 */

#ifndef SIMPLEMATRIXPATTERN_H_
#define SIMPLEMATRIXPATTERN_H_

#include "MatrixPattern.h"

template<int COLS, int ROWS>
class SimpleMatrixPattern: public MatrixPattern {
public:
	typedef int ValueArray[COLS][ROWS];

	SimpleMatrixPattern(ValueArray& values, int pwmSteps);
	virtual ~SimpleMatrixPattern();
	virtual int getPWMSteps() const;
	virtual int getRowCount() const;
	virtual int getColumnCount() const;
	virtual int getValue(int row, int column) const;
	virtual int const* operator[](int columnIndex) const;
	virtual int* operator[](int columnIndex);

private:
	int pwmSteps;
	ValueArray& values;
};

template<int COLS, int ROWS>
SimpleMatrixPattern<COLS, ROWS>::SimpleMatrixPattern(
		ValueArray& valuesIn, int pwnStepsIn) :
		pwmSteps(pwnStepsIn), values(valuesIn) {
}

template<int COLS, int ROWS>
SimpleMatrixPattern<COLS, ROWS>::~SimpleMatrixPattern() {
}

template<int COLS, int ROWS>
int SimpleMatrixPattern<COLS, ROWS>::getPWMSteps() const {
	return pwmSteps;
}

template<int COLS, int ROWS>
int SimpleMatrixPattern<COLS, ROWS>::getRowCount() const {
	return ROWS;
}

template<int COLS, int ROWS>
int SimpleMatrixPattern<COLS, ROWS>::getColumnCount() const {
	return COLS;
}

template<int COLS, int ROWS>
int SimpleMatrixPattern<COLS, ROWS>::getValue(int row, int column) const {
	return values[column][row];
}

template<int COLS, int ROWS>
int const* SimpleMatrixPattern<COLS, ROWS>::operator[](
		int columnIndex) const {
	return values[columnIndex];
}

template<int COLS, int ROWS>
int* SimpleMatrixPattern<COLS, ROWS>::operator[](int columnIndex) {
	return values[columnIndex];
}

#endif /* CONCRETEMATRIXPATTERN_H_ */
