/*
 * Bag.h
 *
 *  Created on: Sep 24, 2014
 *      Author: Dad
 */

#ifndef BAG_H_
#define BAG_H_

// Minimal class to replace std::vector
template<typename Data>
class Bag {
public:
    Bag();
    Bag(int count, Data* data);
    virtual ~Bag();
    Bag(Bag<Data> const &other);
    Bag& operator=(Bag<Data> const &other);
    void push_back(Data& x);
    int size() const;
    Data const &operator[](int idx) const ;
    Data& operator[](int idx);
    void remove(int idx);

    static Data* create(Data& d);
private:
    void resize();

    int dataSize; // Stores no. of actually stored objects
    int capacity; // Stores allocated capacity
    Data *data; // Stores data
};

#endif /* BAG_H_ */
