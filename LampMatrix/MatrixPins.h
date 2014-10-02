/*
 * MatrixPins.h
 *
 *  Created on: Sep 26, 2014
 *      Author: Dad
 */

#ifndef MATRIXPINS_H_
#define MATRIXPINS_H_

#include "MatrixPattern.h"
#include "OutputPins.h"
#include "Arduino.h"

typedef unsigned long Time;

class MatrixPins {
  static const int PWM_STEPS = 100;
  public:
  	MatrixPins(const OutputPins& cols, const OutputPins& rows, Time timPerColumn);
	MatrixPins(const MatrixPins& source);
	~MatrixPins();
	MatrixPins& operator=(const MatrixPins& other);
	void initialize();
	void refresh(Time nowMs);
	void setPattern(MatrixPattern* pattern);
  private:
	Time refreshRate;
	Time* pwmCutoffs;
	Time* colStarts;
	Time* colStops;
    Time timePerColumn;
	OutputPins columns;
	OutputPins rows;
	MatrixPattern* currentPattern;
};


#endif /* MATRIXPINS_H_ */
