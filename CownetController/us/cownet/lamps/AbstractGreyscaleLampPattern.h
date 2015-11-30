/*
 * AbstractGreyscaleLampPattern.h
 *
 *  Created on: Nov 4, 2015
 *      Author: jfitzpatrick
 */

#ifndef us_cownet_lamps_ABSTRACTGREYSCALELAMPPATTERN_H_
#define us_cownet_lamps_ABSTRACTGREYSCALELAMPPATTERN_H_

#include "LampPattern.h"

namespace us_cownet_lamps {

class AbstractGreyscaleLampPattern : public LampPattern {
public:
	static const int GREYSCALE_BITS = 8;

	AbstractGreyscaleLampPattern();
	AbstractGreyscaleLampPattern(int startPosition);
	virtual ~AbstractGreyscaleLampPattern();
	virtual bool getLamp(int index);
	virtual void setStartPosition(int startPosition);
	virtual void attached();
	virtual void endOfMatrixSync();

protected:
	virtual int getLampGreyValue(int ndx) = 0;
	virtual void greyscaleEndOfSync();
	virtual void setCycleStartPosition(int startPosition);

private:
	// position in the refresh cycle
	int cycleCount;
	// position to start the cycle on attached()
	int cycleStart;
};

} /* namespace us_cownet_lamps */

#endif /* us_cownet_lamps_ABSTRACTGREYSCALELAMPPATTERN_H_ */
