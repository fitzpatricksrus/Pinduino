/*
 * MatrixPins.h
 *
 *  Created on: Nov 7, 2014
 *      Author: Dad
 */

#ifndef PINS_MATRIXPINS_H_
#define PINS_MATRIXPINS_H_

#include "../pins/MatrixPattern.h"

namespace pins {

class MatrixPins {
public:
	MatrixPins();
	virtual ~MatrixPins();
	virtual void initPins() = 0;
    virtual void setPattern(MatrixPattern* pattern) = 0;
    virtual void latch() = 0;
};

} /* namespace pins */

#endif /* PINS_MATRIXPINS_H_ */
