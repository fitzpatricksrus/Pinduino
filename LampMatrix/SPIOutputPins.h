/*
 * SPIOutputPins.h
 *
 *  Created on: Oct 5, 2014
 *      Author: Dad
 */

#ifndef SPIOUTPUTPINS_H_
#define SPIOUTPUTPINS_H_

#include "OutputPins.h"

class SPIOutputPins : public OutputPins {
public:
	SPIOutputPins(uint8_t valueCount, int slaveSelectPin, int clockPin, int dataPin);
	SPIOutputPins(const SPIOutputPins& source);
	virtual ~SPIOutputPins();
	virtual SPIOutputPins& operator=(const SPIOutputPins& other);

	virtual void initializePins(int value);
    virtual void initializePins(bool value);
    virtual int getPin(uint8_t pinNdx) const;
    virtual int operator[](uint8_t pinNdx) const;
    virtual void setPin(uint8_t pinNdx, int value);
    virtual void setPins(int* values);
    virtual void setPins(int value);
    virtual void setPin(uint8_t pinNdx, bool value);
    virtual void setPins(bool* values);
    virtual void setPins(bool value);
    virtual uint8_t getPinCount() const;
    virtual void latch();

private:
    uint8_t valueCount;
    uint8_t* values;
    uint8_t SSPin;
    uint8_t SCKPin;
    uint8_t MOSIPin;
};

#endif /* SPIOUTPUTPINS_H_ */
