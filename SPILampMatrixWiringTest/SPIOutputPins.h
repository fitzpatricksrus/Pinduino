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
	SPIOutputPins(byte valueCount, byte slaveSelectPin_ST_CP = 10, byte clockPin_SH_CP = 13, byte dataPin_DS = 11);
	SPIOutputPins(const SPIOutputPins& source);
	virtual ~SPIOutputPins();
	virtual SPIOutputPins& operator=(const SPIOutputPins& other);

	virtual void initPins() const;
    virtual bool getPin(byte pinNdx) const;
    virtual void setPin(byte pinNdx, bool value);
    virtual void set32Pins(long value);
    virtual void setAllPins(byte* value);
    virtual byte getPinCount() const;
    virtual void latch();

    SPIOutputPins& slaveSelectPin(byte pinNumber);
    SPIOutputPins& clockPin(byte pinNumber);
    SPIOutputPins& dataPin(byte pinNumber);

    byte getSlavePin() const;
    byte getClockPin() const;
    byte getDataPin() const;

private:
    byte valueCount;
    byte encodedByteCount;
    byte* encodedBytes;
    byte SSPin;
    byte SCKPin;
    byte MOSIPin;
};

#endif /* SPIOUTPUTPINS_H_ */
