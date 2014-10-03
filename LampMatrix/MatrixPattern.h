/*
 * MatrixPattern.h
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#ifndef MATRIXPATTERN_H_
#define MATRIXPATTERN_H_

class MatrixPattern {
  public:
    virtual ~MatrixPattern();
    virtual int getPWMSteps() const;
    virtual int getRowCount() const = 0;
    virtual int getColumnCount() const = 0;
    virtual int getValue(int row, int column) const = 0;
    virtual int const* operator[](int columnIndex) const = 0;
    virtual int* operator[](int columnIndex) = 0;
};

#endif /* MATRIXPATTERN_H_ */
