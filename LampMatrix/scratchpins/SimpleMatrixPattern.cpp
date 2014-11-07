/*
 * SimpleMatrixPattern.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: Dad
 */

#include "SimpleMatrixPattern.h"

namespace pins {

template<byte cols, byte rows>
SMatrixPattern<cols, rows>::SMatrixPattern(bool** valuesIn)
: values(valuesIn)
{
}

template <byte cols, byte rows>
SMatrixPattern<cols,rows>::~SMatrixPattern() {
}

} /* namespace pins */
