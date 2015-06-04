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

namespace us_cownet_lamps_simple {

using namespace us_cownet_lamps;

class SimpleGreyscaleLampMatrix : public GreyscaleLampMatrix {
public:
	SimpleGreyscaleLampMatrix(LampMatrix* matrix);
	virtual ~SimpleGreyscaleLampMatrix();

	virtual GreyscaleLampPattern* getPattern();
	virtual void setPattern(GreyscaleLampPattern* lamps);
	virtual void setSyncCallback(Callback* callback);

private:
	friend void SimpleGreyscaleLampMatrix_Callback();
	static SimpleGreyscaleLampMatrix* activeMatrix;
	void tock();

	LampMatrix* matrix;
	Callback* callback;
	GreyscaleLampPattern* pattern;
	SimpleLampPattern patterns[8];
	int tickNumber;
};

} /* namespace us_cownet_lamps_simple */

#endif /* SIMPLEGREYSCALELAMPMATRIX_H_ */
