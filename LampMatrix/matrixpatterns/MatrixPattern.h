/*
 * MatrixPattern.h
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#ifndef MATRIXPATTERN_H_
#define MATRIXPATTERN_H_

#include <Arduino.h>

class MatrixPattern {
  public:
    virtual ~MatrixPattern();
    virtual byte getPWMSteps() const = 0;
    virtual byte getRowCount() const = 0;
    virtual byte getColumnCount() const = 0;
    virtual byte getValue(byte row, byte column) const = 0;
    virtual byte const* operator[](byte columnIndex) const = 0;
    virtual byte* operator[](byte columnIndex) = 0;
};

#endif /* MATRIXPATTERN_H_ */
