/*
 * LampMatrix.h
 *
 *  Created on: Jan 25, 2015
 *      Author: Dad
 */

#ifndef LAMPMATRIX_H_
#define LAMPMATRIX_H_

#include <Arduino.h>

class LampMatrix {
public:
	LampMatrix();
	virtual ~LampMatrix();

	virtual void setColumn(byte column, byte values) = 0;
};

#endif /* LAMPMATRIX_H_ */
