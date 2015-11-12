/*
 * DebugLampMatrix.h
 *
 *  Created on: Nov 10, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_
#define US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_

#include "../LampMatrix.h"
#include "../LampPattern.h"
#include "../../timers/Callback.h"

namespace us_cownet_lamps_controllers {

using us_cownet_lamps::LampPattern;
using us_cownet_lamps::LampMatrix;
using us_cownet_timers::CallbackFor;

class DebugLampMatrix : public LampMatrix {
public:
	DebugLampMatrix(long refreshFrequency);
	virtual ~DebugLampMatrix();

	virtual LampPattern* getPattern();
	virtual void setPattern(LampPattern* lamps);

private:
	void tock();

	long refreshFrequency;
	LampPattern* pattern;
	CallbackFor<DebugLampMatrix> tockCallback;
};

} /* namespace us_cownet_lamps_controllers */

#endif /* US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_ */
