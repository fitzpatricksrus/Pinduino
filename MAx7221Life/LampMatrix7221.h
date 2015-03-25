/*
 * LampMatrix.h
 *
 *  Created on: Jan 24, 2015
 *      Author: Dad
 */

#ifndef LAMPMATRIX7221_H_
#define LAMPMATRIX7221_H_

#include "LampMatrix.h"
#include <Max7221.h>

class LampMatrix7221 : public LampMatrix {
public:
	LampMatrix7221(byte selectPin);
	virtual ~LampMatrix7221();

	virtual void setColumn(byte column, byte values);

private:
	Max7221* max7221;
	byte selectPin;
};

#endif /* LAMPMATRIX7221_H_ */
