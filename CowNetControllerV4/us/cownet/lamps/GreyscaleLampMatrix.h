#ifndef US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_
#define US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_

#include "GreyscaleLampPattern.h"

namespace us_cownet_lamps {

class GreyscaleLampMatrix {
public:
	typedef void (Callback)();

	GreyscaleLampMatrix();
	virtual ~GreyscaleLampMatrix();

	virtual GreyscaleLampPattern* getPattern() = 0;

	virtual void setPattern(GreyscaleLampPattern* lamps) = 0;

	virtual void setSyncCallback(Callback* callback) = 0;
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_ */
