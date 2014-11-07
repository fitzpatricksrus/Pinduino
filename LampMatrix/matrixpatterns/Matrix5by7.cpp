/*
 * Matrix5by7.cpp
 *
 *  Created on: Oct 2, 2014
 *      Author: Dad
 */

#include "Matrix5by7.h"
#include "SimpleMatrixPattern.h"
#include <Arduino.h>

namespace matrixpatterns {

static SimpleMatrixPattern<5,6>::ValueArray MATRIX_VALUES1 = {
	    { 59,  9, 00,  0,  9, 59 },
	    {  9, 59,  9,  9, 59,  9 },
	    {  0,  9, 59, 59,  9,  0 },
	    {  9, 59,  9,  9, 59,  9 },
	    { 59,  9,  0,  0,  9, 59 },
};
static SimpleMatrixPattern<5,6> PATTERN1(MATRIX_VALUES1, 60);

static SimpleMatrixPattern<5,6>::ValueArray MATRIX_VALUES2 = {
	    { 10, 50, 58, 58, 50, 10 },
	    { 50, 10, 50, 50, 10, 50 },
	    { 58, 50, 10, 10, 50, 58 },
	    { 50, 10, 50, 50, 10, 50 },
	    { 10, 50, 58, 58, 50, 10 },
};
static SimpleMatrixPattern<5,6> PATTERN2(MATRIX_VALUES2, 60);

MatrixPattern* Matrix5by7::getPattern1() {
	return &PATTERN1;
}
MatrixPattern* Matrix5by7::getPattern2() {
	return &PATTERN2;
}

} // namespace matrixpatterns
