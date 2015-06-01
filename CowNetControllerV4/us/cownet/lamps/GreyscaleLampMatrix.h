#ifndef US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_
#define US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_

#include "GreyscaleLampPattern.h"

namespace us_cownet_lamps {

class GreyscaleLampMatrix {
public:
	typedef void (Runnable)();

	GreyscaleLampMatrix();
	virtual ~GreyscaleLampMatrix();

	GreyscaleLampPattern* getPattern();

	void setPattern(GreyscaleLampPattern* lamps);

	void setSyncCallback(Runnable* callback);
};

} /* namespace us_cownet_lamps */

#endif /* US_COWNET_LAMPS_GREYSCALELAMPMATRIX_H_ */
