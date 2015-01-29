/*
 * DecayLampMatrix.cpp
 *
 *  Created on: Jan 28, 2015
 *      Author: Dad
 */

#include "DecayLampMatrix.h"

DecayLampMatrix::DecayLampMatrix(LampMatrix* driverMatrixIn, int decayRateIn)
: driverMatrix(driverMatrixIn), decayRate(decayRateIn)
{
}

DecayLampMatrix::~DecayLampMatrix() {
}

void DecayLampMatrix::init() {
	for (byte i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			decayValue[i][j] = 0;
		}
	}
	driverMatrix->init();
}

void DecayLampMatrix::setColumn(byte column, byte values) {
	for (int i = 0; i < 8; i++) {
		if (values & (1 << i)) {
			decayValue[column][i] = decayRate;
		}
	}
	tick();
}

void DecayLampMatrix::tick() {
	for (byte i = 0; i < 8; i++) {
		byte value = 0;
		for (int j = 0; j < 8; j++) {
			value = value << 1;
			if (decayValue[i][j] > 0) {
				value |= 1;
			}
			decayValue[i][j] = max(decayValue[i][j] - 1, 0);
		}
		driverMatrix->setColumn(i, value);
	}
}


