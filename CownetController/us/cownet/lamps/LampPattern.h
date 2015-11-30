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

	/*
	 The life cycle for using a pattern looks like this

	 attached()
	 --getLampCount()
	 --getLamp()
	 --endOfMatrixSync() // callback is called here
	 detached()

	 */

	virtual void attached();

	virtual int getLampCount() = 0;

	virtual bool getLamp(int index) = 0;

	virtual void endOfMatrixSync();

	virtual void detached();

	/*
	 Optimization points.  By defaul these just call getLampCount and getLamp.  Some matrix implementations
	 are more efficient working on banks of 8 lamps at a time.  Subclasses can override these to make
	 a more efficient implementation.
	 */

	virtual int getLampBankCount();

	virtual byte getLampBank(int x);

	/*
	 Start the refresh sequence from the beginning.
	 */
	virtual void reset();

	/*
	 Used only by pattern containers.  isDone() should return true when the
	 pattern has displayed its entire state sequence once.  This has no affect
	 on the lamp matrix, which will continue to cycle through columns.  Containers
	 can decide how to proceed and may reset() the pattern, replace it, or
	 continue to refresh the matrix with it.
	 */
	virtual bool isDone();
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_LAMPPATTERN_H_ */
