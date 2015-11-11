/*
 * DebugLampMatrix.h
 *
 *  Created on: Nov 10, 2015
 *      Author: Dad
 */

#ifndef US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_
#define US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_

#include "../LampMatrix.h"

namespace us_cownet_lamps_controllers {

using us_cownet_lamps::LampMatrix;

class DebugLampMatrix : public LampMatrix {
public:
	DebugLampMatrix();
	virtual ~DebugLampMatrix();
};

} /* namespace us_cownet_lamps_controllers */

#endif /* US_COWNET_LAMPS_CONTROLLERS_DEBUGLAMPMATRIX_H_ */
