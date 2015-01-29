/*
 * DecayLampMatrix.h
 *
 *  Created on: Jan 28, 2015
 *      Author: Dad
 */

#ifndef DECAYLAMPMATRIX_H_
#define DECAYLAMPMATRIX_H_

#include "LampMatrix.h"

class DecayLampMatrix : public LampMatrix {
public:
	DecayLampMatrix(LampMatrix* driverMatrix, int decayRate);
	virtual ~DecayLampMatrix();

	virtual void init();
	virtual void setColumn(byte column, byte values);
	virtual void tick();

private:
	LampMatrix* driverMatrix;
	int decayValue[8][8];
	int decayRate;
};

#endif /* DECAYLAMPMATRIX_H_ */
