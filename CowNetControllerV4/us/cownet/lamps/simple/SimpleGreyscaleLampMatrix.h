/*
 * SimpleGreyscaleLampMatrix.h
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#ifndef SIMPLEGREYSCALELAMPMATRIX_H_
#define SIMPLEGREYSCALELAMPMATRIX_H_

#include "../GreyscaleLampMatrix.h"

namespace us_cownet_lamps_simple {

using namespace us_cownet_lamps;

class SimpleGreyscaleLampMatrix : public GreyscaleLampMatrix {
public:
	SimpleGreyscaleLampMatrix();
	virtual ~SimpleGreyscaleLampMatrix();

	virtual GreyscaleLampPattern* getPattern();
	virtual void setPattern(GreyscaleLampPattern* lamps);
	virtual void setSyncCallback(Callback* callback);

private:
	Callback* callback;
	GreyscaleLampPattern* pattern;
};

} /* namespace us_cownet_lamps_simple */

#endif /* SIMPLEGREYSCALELAMPMATRIX_H_ */
