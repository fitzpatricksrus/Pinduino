/*
 * ConcreteMatrixPattern.h
 *
 *  Created on: Sep 28, 2014
 *      Author: Dad
 */

#ifndef CONCRETEMATRIXPATTERN_H_
#define CONCRETEMATRIXPATTERN_H_

#include "MatrixPattern.h"

template <int COLS, int ROWS>
class ConcreteMatrixPattern : public MatrixPattern {
public:
	typedef int ValueArray[COLS][ROWS];

	ConcreteMatrixPattern(ValueArray& values, int pwmSteps);
    virtual ~ConcreteMatrixPattern();
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

template <int COLS, int ROWS>
ConcreteMatrixPattern<COLS,ROWS>::ConcreteMatrixPattern(ValueArray& valuesIn, int pwnStepsIn)
: pwmSteps(pwnStepsIn), values(valuesIn)
{
}

template <int COLS, int ROWS>
ConcreteMatrixPattern<COLS, ROWS>::~ConcreteMatrixPattern() {
}

template <int COLS, int ROWS>
int ConcreteMatrixPattern<COLS, ROWS>::getPWMSteps() const {
	return pwmSteps;
}

template <int COLS, int ROWS>
int ConcreteMatrixPattern<COLS, ROWS>::getRowCount() const {
	return ROWS;
}

template <int COLS, int ROWS>
int ConcreteMatrixPattern<COLS, ROWS>::getColumnCount() const {
	return COLS;
}

template <int COLS, int ROWS>
int ConcreteMatrixPattern<COLS, ROWS>::getValue(int row, int column) const {
	return values[column][row];
}

template <int COLS, int ROWS>
int const* ConcreteMatrixPattern<COLS, ROWS>::operator[](int columnIndex) const {
	return values[columnIndex];
}

template <int COLS, int ROWS>
int* ConcreteMatrixPattern<COLS, ROWS>::operator[](int columnIndex) {
	return values[columnIndex];
}

#endif /* CONCRETEMATRIXPATTERN_H_ */
