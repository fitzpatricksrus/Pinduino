/*
 * GreyscaleLampPattern.h
 *
 *  Created on: Oct 30, 2015
 *      Author: jfitzpatrick
 */

#ifndef GREYSCALELAMPPATTERN_H_
#define GREYSCALELAMPPATTERN_H_

#include "LampPattern.h"
#include "SimpleMatrixLampPattern.h"
#include "LinearLampPattern.h"

namespace us_cownet_lamps {


class GreyscaleLampPattern: public LinearLampPattern {
public:
	static const int GREYSCALE_BITS = 8;

	GreyscaleLampPattern();

	// scratchSpace size == columnCount * GREYSCALE_BITS;
	GreyscaleLampPattern(int greyPattern[], int scratchSpace[], int columnCount);

	GreyscaleLampPattern(int greyPattern[], int scratchSpace[], int columnCount, int startPosition);

	virtual ~GreyscaleLampPattern();

	virtual byte getColumn(int x);

	virtual int getColCount();

	virtual void setStartPosition(int startPosition);

	virtual void attached();

	virtual void endOfMatrixSync();

	virtual void setPattern(int greyPattern[], int columnCount);

	virtual void setPattern(int greyPattern[], int columnCount, int startPosition);

private:
	// position in the refresh cycle
	int cycleCount;
	// position to start the cycle on attached()
	int cycleStart;
	// component lamp patters.  one for each greyscale bit
	SimpleMatrixLampPattern patterns[GREYSCALE_BITS];
	// storage used when generating SimpleMatrixLampPatterns
	int* scratchSpace;
};

} /* namespace us_cownet_lamps */

#endif /* GREYSCALELAMPPATTERN_H_ */
