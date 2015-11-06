/*
 * Max7221LampMatrix.h
 *
 *  Created on: Oct 28, 2015
 *      Author: jfitzpatrick
 */

#ifndef us_cownet_lamps_tests_MAX7221LAMPMATRIX_H_
#define us_cownet_lamps_tests_MAX7221LAMPMATRIX_H_

#include "../LampPattern.h"
#include "../LampMatrix.h"
#include "../../timers/Callback.h"
#include "../../utils/Notifier.h"
#include "../../utils/Listener.h"
#include "../../utils/Notifier.h"
#include <Max7221.h>

namespace us_cownet_lamps_controllers {

using us_cownet_lamps::LampPattern;
using us_cownet_lamps::LampMatrix;
using us_cownet_timers::CallbackFor;

class Max7221LampMatrix: public LampMatrix {
public:
	Max7221LampMatrix();
	Max7221LampMatrix(long refreshFrequency, int selectPin);
	virtual ~Max7221LampMatrix();

	virtual LampPattern* getPattern();

	/*
	 detached() is called on the current pattern is there is one.  Then call
	 attached on the new lamp pattern.  The entire life cycle looks like this:

	 attached()
	 --getColCount()
	 --getColumn()
	 --endOfMatrixSync() // callback is called here
	 detached()

	 */
	virtual void setPattern(LampPattern* lamps);

private:
	void tock();

	long refreshFrequency;
	LampPattern* pattern;
	CallbackFor<Max7221LampMatrix> thisCallback;
	Max7221 max7221;
};

} /* namespace us_cownet_lamps_tests */

#endif /* MAX7221LAMPMATRIX_H_ */
