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
    virtual void initializePins(int value) = 0;
    virtual void initializeDigitalPins(int value) = 0;
    virtual int getPin(uint8_t pinNdx) const = 0;
    virtual int operator[](uint8_t pinNdx) const = 0;
    virtual void setAnalogPin(uint8_t pinNdx, int value) = 0;
    virtual void setAnalogPins(int* values) = 0;
    virtual void setAnalogPins(int value) = 0;
    virtual void setDigitalPin(uint8_t pinNdx, int value) = 0;
    virtual void setDigitalPins(int* values) = 0;
    virtual void setDigitalPins(int value) = 0;
    virtual uint8_t getPinCount() const = 0;

    virtual void latch() = 0;

    void debug();
    virtual void debug(const char* pre, const char* post) = 0;
};

#endif /* OUTPUTPINS_H_ */
