/*
 * LampMatrix.h
 *
 *  Created on: Oct 9, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_LAMPMATRIX_H_
#define US_COWNET_LAMPS_LAMPMATRIX_H_

#include "LampPattern.h"
#include "../timers/Callback.h"

namespace us_cownet_lamps {

using us_cownet_timers::Callback;

class LampMatrix {
public:
	LampMatrix();
	virtual ~LampMatrix();

	virtual LampPattern* getPattern() = 0;

	/*
	 detached() is called on the current pattern is there is one.  Then call
	 attached on the new lamp pattern.  The entire life cycle looks like this:

	 attached()
	 --getColCount()
	 --getColumn()
	 --endOfMatrixSync() // callback is called here
	 detached()

	 */
	virtual void setPattern(LampPattern* lamps) = 0;

};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_LAMPMATRIX_H_ */
