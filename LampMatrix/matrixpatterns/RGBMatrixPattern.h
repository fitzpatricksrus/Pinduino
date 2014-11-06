/*
 * RGBMatrixPattern.h
 *
 *  Created on: Nov 2, 2014
 *      Author: Dad
 */

#ifndef RGBMATRIXPATTERN_H_
#define RGBMATRIXPATTERN_H_

#include "Arduino.h"
#include "MatrixPattern.h"

class RGBMatrixPattern {
public:
	enum RGBComponent { RED, GREEN, BLUE } ;

	RGBMatrixPattern();
	virtual ~RGBMatrixPattern();

	virtual byte getRowCount() const = 0;
	virtual byte getColumnCount() const = 0;
	virtual byte getValue(RGBComponent comp, byte row, byte column) const = 0;
	virtual const MatrixPattern* operator[](RGBComponent comp) const = 0;
	virtual MatrixPattern* operator[](RGBComponent comp) = 0;
};

#endif /* RGBMATRIXPATTERN_H_ */
