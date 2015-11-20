/*
 * SimpleGreyscaleLampPattern.h
 *
 *  Created on: Nov 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEGREYSCALELAMPPATTERN_H_
#define SIMPLEGREYSCALELAMPPATTERN_H_

#include "GreyscaleLampPattern.h"
#include "LampPattern.h"
#include "SimpleMatrixLampPattern.h"


namespace us_cownet_lamps {

class SimpleGreyscaleLampPattern: public GreyscaleLampPattern {
public:
	static const int GREYSCALE_BITS = 8;

	SimpleGreyscaleLampPattern();

	// scratchSpace size == columnCount * GREYSCALE_BITS;
	SimpleGreyscaleLampPattern(int greyPattern[], int scratchSpace[], int columnCount);

	SimpleGreyscaleLampPattern(int greyPattern[], int scratchSpace[], int columnCount, int startPosition);

	virtual ~SimpleGreyscaleLampPattern();

	virtual byte getColumn(int x);

	virtual bool getLamp(int x);

	virtual int getColCount();

	virtual int getLampCount();

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

#endif /* SIMPLEGREYSCALELAMPPATTERN_H_ */
