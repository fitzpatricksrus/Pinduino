/*
 * GreyscaleLampPattern.h
 *
 *  Created on: Oct 30, 2015
 *      Author: jfitzpatrick
 */

#ifndef GREYSCALELAMPPATTERN_H_
#define GREYSCALELAMPPATTERN_H_

#include "LampPattern.h"
#include "SimpleLampPattern.h"

namespace us_cownet_lamps {

class GreyscaleLampPattern: public LampPattern {
public:
	static const int GREYSCALE_BITS = 8;

	GreyscaleLampPattern();

	template <int columnCountIn, int scratchSizeIn>
	GreyscaleLampPattern(int (&greyPattern)[columnCountIn], int (&scratchSpaceIn)[scratchSizeIn], int startPosition = 0)
	: cycleCount(0), cycleStart(0), patterns(), scratchSpace(scratchSpaceIn)
	{
		setPattern(greyPattern, scratchSpaceIn, columnCountIn, startPosition);
	}

	// scratchSpace size == columnCount * GREYSCALE_BITS;
	GreyscaleLampPattern(int greyPattern[], int scratchSpace[], int columnCount, int startPosition = 0);

	virtual ~GreyscaleLampPattern();

	virtual byte getColumn(int x);

	virtual int getColCount();

	virtual void setStartPosition(int startPosition);

	virtual void attached();

	virtual void endOfMatrixSync();

	virtual void setPattern(int greyPattern[], int scratchSpaceIn[], int columnCount, int startPosition = 0);

private:
	// position in the refresh cycle
	int cycleCount;
	// position to start the cycle on attached()
	int cycleStart;
	// component lamp patters.  one for each greyscale bit
	SimpleLampPattern patterns[GREYSCALE_BITS];
	// storage used when generating SimpleMatrixLampPatterns
	int* scratchSpace;
};

} /* namespace us_cownet_lamps */

#endif /* GREYSCALELAMPPATTERN_H_ */
