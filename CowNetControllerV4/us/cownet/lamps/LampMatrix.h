/*
 * LampMatrix.h
 *
 *  Created on: May 31, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_LAMPMATRIX_H_
#define US_COWNET_LAMPS_LAMPMATRIX_H_

#include <Arduino.h>
#include "LampPattern.h"
#include "../timers/Callback.h"

namespace us_cownet_lamps {

using namespace us_cownet_timers;

class LampMatrix {
public:
	LampMatrix();
	virtual ~LampMatrix();
	virtual LampPattern* getPattern() = 0;
	virtual void setPattern(LampPattern* lamps) = 0;
	virtual void setSyncCallback(Callback* callback) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_LAMPMATRIX_H_ */
