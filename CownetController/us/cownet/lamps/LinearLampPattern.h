/*
 * LinearLampPattern.h
 *
 *  Created on: Oct 13, 2015
 *      Author: jfitzpatrick
 */

#ifndef LINEARLAMPPATTERN_H_
#define LINEARLAMPPATTERN_H_

#include "LampPattern.h"

namespace us_cownet_lamps {

class LinearLampPattern: public LampPattern {
public:
	LinearLampPattern();
	virtual ~LinearLampPattern();

	virtual byte getColumn(int x);

	virtual int getColCount();

	virtual int getLampCount() = 0;

	virtual bool getLamp(int x, int y);

	virtual bool getLamp(int index) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* LINEARLAMPPATTERN_H_ */
