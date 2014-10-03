/*
 * Matrix5by7.h
 *
 *  Created on: Oct 2, 2014
 *      Author: Dad
 */

#ifndef MATRIX5BY7_H_
#define MATRIX5BY7_H_

#include "ConcreteMatrixPattern.h"

class Matrix5by7 {
public:
	static ConcreteMatrixPattern<5, 6>& getPattern1();
	static ConcreteMatrixPattern<5, 6>& getPattern2();
};

#endif /* MATRIX5BY7_H_ */
