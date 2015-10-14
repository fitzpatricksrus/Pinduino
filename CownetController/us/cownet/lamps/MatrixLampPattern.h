/*
 * MatrixLampPattern.h
 *
 *  Created on: Oct 13, 2015
 *      Author: jfitzpatrick
 */

#ifndef MATRIXLAMPPATTERN_H_
#define MATRIXLAMPPATTERN_H_

#include "LampPattern.h"

namespace us_cownet_lamps {

class MatrixLampPattern: public LampPattern {
public:
	MatrixLampPattern();
	virtual ~MatrixLampPattern();

	virtual byte getColumn(int x);

	virtual int getLampCount();

	virtual int getColCount() = 0;

	virtual bool getLamp(int x, int y) = 0;

	virtual bool getLamp(int index);
};

} /* namespace us_cownet_lamps */

#endif /* MATRIXLAMPPATTERN_H_ */
