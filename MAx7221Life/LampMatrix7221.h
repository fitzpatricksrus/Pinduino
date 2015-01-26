/*
 * LampMatrix.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Dad
 */

#ifndef LAMPMATRIX7221_H_
#define LAMPMATRIX7221_H_

#include "LampMatrix.h"

class LampMatrix7221 : public LampMatrix {
public:
	LampMatrix7221();
	virtual ~LampMatrix7221();

	virtual void setColumn(byte column, byte values);

private:
	Max7221* max7221;
};

#endif /* LAMPMATRIX7221_H_ */
