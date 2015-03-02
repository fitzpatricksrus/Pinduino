/*
 * CircularBuffer.h
 *
 *  Created on: Mar 1, 2015
 *      Author: Dad
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <Arduino.h>

template <class T>
class CircularBuffer {
public:
	CircularBuffer(T* storage, byte size);
	virtual ~CircularBuffer();

	virtual bool isNotEmpty() const volatile;
	virtual T peek() const volatile;
	virtual T pop() volatile;
	virtual void push(T value) volatile;

protected:
	T* storage;
	byte size;
	byte pushPos;
	byte popPos;
};

template<class T>
inline CircularBuffer<T>::CircularBuffer(T* storageIn, byte sizeIn)
: storage(storageIn), size(sizeIn), pushPos(0), popPos(0)
{
}

template<class T>
inline CircularBuffer<T>::~CircularBuffer() {
}

template<class T>
inline bool CircularBuffer<T>::isNotEmpty() const volatile {
	return pushPos != popPos;
}

template<class T>
inline T CircularBuffer<T>::peek() const volatile {
	return storage[popPos];
}

template<class T>
inline T CircularBuffer<T>::pop() volatile {
	T result = storage[popPos];
	popPos = (popPos + 1) % size;
	return result;
}

template<class T>
inline void CircularBuffer<T>::push(T value) volatile {
	storage[pushPos] = value;
	pushPos = (pushPos + 1) % size;
}

#endif /* CIRCULARBUFFER_H_ */
