/*
 * BitBuffer.h
 *
 *  Created on: May 3, 2016
 *      Author: jfitzpatrick
 */

#ifndef BITBUFFER_H_
#define BITBUFFER_H_

#include <arduino.h>

class BitBuffer {
public:
	BitBuffer(byte* storage, int size);
	virtual ~BitBuffer();

	virtual byte* push(bool valueIn) = 0;

private:
	byte buffer;
	int size;
	int position;
};

template <int size>
class BitBufferOfSize : public BitBuffer {
public:
	BitBufferOfSize();
	~BitBufferOfSize();
	byte* push(bool valueIn) = 0;

};


#endif /* BITBUFFER_H_ */
