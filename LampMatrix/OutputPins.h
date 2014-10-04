/*
 * OutputPins.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#ifndef OUTPUTPINS_H_
#define OUTPUTPINS_H_

#include <Arduino.h>

class OutputPins {
public:
    OutputPins(int pinCount, int pins[]);
    OutputPins(const OutputPins& source);
	~OutputPins();
	OutputPins& operator=(const OutputPins& other);
    void initializePins(int value);
    void initializeDigitalPins(int value);
    int getPin(int pinNdx) const;
    int operator[](int pinNdx) const;
    void setAnalogPin(int pinNdx, int value);
    void setAnalogPins(int* values);
    void setAnalogPins(int value);
    void setDigitalPin(int pinNdx, int value);
    void setDigitalPins(int* values);
    void setDigitalPins(int value);
    int getPinCount() const;

    void debug();
    void debug(const char* pre, const char* post);

private:
    int* pinNumber;
    int* pinValue;
    int pinCount;
};

inline int OutputPins::getPinCount() const {
    return pinCount;
}

inline int OutputPins::getPin(int pinNdx) const {
    return pinValue[pinNdx];
}

inline int OutputPins::operator[](int pinNdx) const {
    return pinValue[pinNdx];
}

#endif /* OUTPUTPINS_H_ */
