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
	driverMatrix->init();
	for (byte i = 0; i < 8; i++) {
		for (byte j = 0; j < 8; j++) {
			decayValue[i][j] = 0;
		}
	}
}

void DecayLampMatrix::setColumn(byte column, byte values) {
	for (byte i = 0; i < 8; i++) {
		if (values & (1 << i)) {
			decayValue[column][i] = decayRate;
		}
	}
}

static byte pack(int values[]) {
	byte result = 0;
	for (int i = 0; i < 8; i++) {
		result = result << 1;
		if (values[i] > 0) {
			result |= 1;
		}
	}
	return result;
}

void DecayLampMatrix::tick() {
	for (byte i = 0; i < 8; i++) {
		for (byte j = 0; j < 8; j++) {
			decayValue[i][j] = max(decayValue[i][j] - 1, 0);
		}
		driverMatrix->setColumn(i, pack(decayValue[i]));
	}
}


