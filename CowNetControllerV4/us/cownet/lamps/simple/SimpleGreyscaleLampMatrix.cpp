/*
 * SimpleGreyscaleLampMatrix.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: jfitzpatrick
 */

#include "SimpleGreyscaleLampMatrix.h"

namespace us_cownet_lamps_simple {

static const int MASK[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
static int INDEX[256];

SimpleGreyscaleLampMatrix* SimpleGreyscaleLampMatrix::activeMatrix = NULL;
void SimpleGreyscaleLampMatrix_Callback() {
	if (SimpleGreyscaleLampMatrix::activeMatrix) {
		SimpleGreyscaleLampMatrix::activeMatrix->tock();
	}
}

SimpleGreyscaleLampMatrix::SimpleGreyscaleLampMatrix(LampMatrix* matrixIn)
: matrix(matrixIn), pattern(0), callback(0), tickNumber(0)
{
	// hey jf - this is really static initialization!
    int next = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < MASK[i]; j++) {
            INDEX[next++] = i;
        }
    }
}

SimpleGreyscaleLampMatrix::~SimpleGreyscaleLampMatrix() {
}

GreyscaleLampPattern* SimpleGreyscaleLampMatrix::getPattern() {
	return pattern;
}

void SimpleGreyscaleLampMatrix::setPattern(GreyscaleLampPattern* lamps) {
    pattern = lamps;
    for (int i = 0; i < 8; i++) {
        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                patterns[i].setLamp(col, row, (lamps->getLamp(col, row) & MASK[i]) != 0);
            }
        }
    }
    tickNumber = 0;
    matrix->setPattern(&patterns[0]);
}

void SimpleGreyscaleLampMatrix::setSyncCallback(Callback* callbackIn) {
	callback = callbackIn;
}

void SimpleGreyscaleLampMatrix::tock() {
    tickNumber = (tickNumber + 1) % 256;
    if (tickNumber == 0 && callback != NULL) {
        (*callback)();
    }
    matrix->setPattern(&patterns[INDEX[tickNumber]]);
}

} /* namespace us_cownet_lamps_simple */
