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
	virtual ~OutputPins() {}
    virtual void initializePins(int value) = 0;
    virtual void initializePins(bool value) = 0;
    virtual int getPin(uint8_t pinNdx) const = 0;
    virtual int operator[](uint8_t pinNdx) const = 0;
    virtual void setPin(uint8_t pinNdx, int value) = 0;
    virtual void setPins(int* values) = 0;
    virtual void setPins(int value) = 0;
    virtual void setPin(uint8_t pinNdx, bool value) = 0;
    virtual void setPins(bool* values) = 0;
    virtual void setPins(bool value) = 0;
    virtual uint8_t getPinCount() const = 0;

    virtual void latch() = 0;

    void debug();
    virtual void debug(const char* pre, const char* post);
};

#endif /* OUTPUTPINS_H_ */
