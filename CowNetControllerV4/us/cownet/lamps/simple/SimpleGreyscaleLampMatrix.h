/*
 * SimpleGreyscaleLampMatrix.h
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEGREYSCALELAMPMATRIX_H_
#define SIMPLEGREYSCALELAMPMATRIX_H_

#include "../LampMatrix.h"
#include "../GreyscaleLampMatrix.h"
#include "SimpleLampPattern.h"
#include "../../timers/Callback.h"

namespace us_cownet_lamps_simple {

using namespace us_cownet_lamps;
using namespace us_cownet_timers;

class SimpleGreyscaleLampMatrix : public GreyscaleLampMatrix {
public:
	SimpleGreyscaleLampMatrix(LampMatrix* matrix);
	virtual ~SimpleGreyscaleLampMatrix();

	virtual GreyscaleLampPattern* getPattern();
	virtual void setPattern(GreyscaleLampPattern* lamps);
	virtual void setSyncCallback(Callback* callback);

private:
	CallbackTo<SimpleGreyscaleLampMatrix> localCallback;
	void tock();

	LampMatrix* matrix;
	GreyscaleLampPattern* pattern;
	Callback* callback;
	SimpleLampPattern patterns[8];
	int tickNumber;
};

} /* namespace us_cownet_lamps_simple */

#endif /* SIMPLEGREYSCALELAMPMATRIX_H_ */
