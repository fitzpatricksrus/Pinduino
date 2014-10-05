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
    OutputPins(uint8_t pinCount, uint8_t pins[]);
    OutputPins(const OutputPins& source);
	~OutputPins();
	OutputPins& operator=(const OutputPins& other);
    void initializePins(int value);
    void initializeDigitalPins(int value);
    int getPin(uint8_t pinNdx) const;
    int operator[](uint8_t pinNdx) const;
    void setAnalogPin(uint8_t pinNdx, int value);
    void setAnalogPins(int* values);
    void setAnalogPins(int value);
    void setDigitalPin(uint8_t pinNdx, int value);
    void setDigitalPins(int* values);
    void setDigitalPins(int value);
    uint8_t getPinCount() const;

    void latch();

    void debug();
    void debug(const char* pre, const char* post);

private:
    uint8_t* pinNumber;
    int* pinValue;
    uint8_t pinCount;
};

inline uint8_t OutputPins::getPinCount() const {
    return pinCount;
}

inline int OutputPins::getPin(uint8_t pinNdx) const {
    return pinValue[pinNdx];
}

inline int OutputPins::operator[](uint8_t pinNdx) const {
    return pinValue[pinNdx];
}

#endif /* OUTPUTPINS_H_ */
