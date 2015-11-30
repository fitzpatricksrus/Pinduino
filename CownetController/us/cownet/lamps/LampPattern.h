/*
 * LampPattern.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_LAMPPATTERN_H_
#define US_COWNET_LAMPS_LAMPPATTERN_H_

#include <Arduino.h>

namespace us_cownet_lamps {

class LampPattern {
public:
	LampPattern();
	virtual ~LampPattern();

	virtual byte getColumn(int x);

	virtual int getColCount();

	virtual int getLampCount() = 0;

	virtual bool getLamp(int index) = 0;

	virtual void attached();

	virtual void endOfMatrixSync();

	/*
	 Used only by pattern containers.  isDone() should return true when the
	 pattern has displayed its entire state sequence once.  This has no affect
	 on the lamp matrix, which will continue to cycle through columns.  Containers
	 can decide how to proceed and may reset() the pattern, replace it, or
	 continue to refresh the matrix with it.
	 */
	virtual bool isDone();

	/*
	 Start the refresh sequence from the beginning.
	 */
	virtual void reset();

	virtual void detached();
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_LAMPPATTERN_H_ */
