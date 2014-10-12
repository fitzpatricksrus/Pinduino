/*
 * Bag.cpp
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#include "Bag.h"

#define MAX_GROWTH 10

// Minimal class to replace std::vector
template <class Data>
Bag<Data>::Bag()
: dataSize(0), capacity(0), data(0)
{
}

template <class Data>
Bag<Data>::Bag(int count, Data* data)
: dataSize(0), capacity(0), data(0)
{
	for (int i = 0; i < count; i++) {
		push_back(data[i]);
	}
}

template <class Data>
Bag<Data>::~Bag() {
    if (data != 0) {
        free(data);
    }
}

template <class Data>
Bag<Data>::Bag(const Bag<Data>& other)
: dataSize(other.dataSize), capacity(other.dataSize), data(0) {
    if (capacity > 0) {
        data = new Data[capacity];
        for (int i = 0; i < other.dataSize; i++) data[i] = other.data[i];
    }
}

template <class Data>
Bag<Data>& Bag<Data>::operator=(Bag<Data> const &other) {
    free(data);
    dataSize = other.dataSize;
    capacity = other.capacity;
    if (capacity > 0) {
        data = new Data[capacity];
        for (int i = 0; i < other.dataSize; i++) data[i] = other.data[i];
    }
    return *this;
}

template <class Data>
void Bag<Data>::push_back(Data& x) {
    if (capacity == dataSize) {
        capacity += MAX_GROWTH;
        resize();
    }
    data[dataSize++] = x;
}

template <class Data>
int Bag<Data>::size() const {
    return dataSize;
}

template <class Data>
Data const &Bag<Data>::operator[](int idx) const {
    return data[idx];
}

template <class Data>
Data &Bag<Data>::operator[](int idx) {
    return data[idx];
}

template <class Data>
void Bag<Data>::remove(int idx) {
    data[idx] = data[dataSize - 1];
    dataSize = dataSize - 1;
    if (capacity - dataSize > MAX_GROWTH) {
        capacity = dataSize;
        resize();
    }
}

template <class Data>
void Bag<Data>::resize() {
    Data* newdata = new Data[capacity];
    for (int i = 0; i < dataSize; i++) newdata[i] = data[i];
    if (data != 0) free(data);
    data = newdata;
}

template <class Data>
Data* Bag<Data>::create(Data& d) {
	return 0;
}
