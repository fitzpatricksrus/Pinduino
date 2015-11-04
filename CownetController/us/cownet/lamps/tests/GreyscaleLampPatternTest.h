/*
 * GreyscaleLampPatternTest.h
 *
 *  Created on: Nov 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef us_cownet_lamps_tests_GREYSCALELAMPPATTERNTEST_H_
#define us_cownet_lamps_tests_GREYSCALELAMPPATTERNTEST_H_

#include "../LampMatrix.h"
#include "../../testing/Test.h"

namespace us_cownet_lamps_tests {

using us_cownet_lamps::LampMatrix;
using us_cownet_testing::Test;

class GreyscaleLampPatternTest: public Test {
public:
	GreyscaleLampPatternTest(LampMatrix* greyMatrix);
	virtual ~GreyscaleLampPatternTest();

	virtual void setup();
	virtual void loop();

private:
	LampMatrix* greyLampMatrix;
};


} /* namespace us_cownet_lamps_tests */

#endif /* us_cownet_lamps_tests_GREYSCALELAMPPATTERNTEST_H_ */
