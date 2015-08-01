/*
 * ArrayList.h
 *
 *  Created on: Jul 28, 2015
 *      Author: jfitzpatrick
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <stddef.h>

namespace us_cownet_util {

template <class T, int maxSize> class ArrayList {
public:
	ArrayList();
	~ArrayList();

	int add(T* obj);
	int remove(T* obj);
	void remove(int ndx);
	bool contains(T* obj);
	int indexOf(T* obj);
	int size();
	T operator[](int ndx) const;

private:
	T* contents[maxSize];
	int count;
};


template<class T, int maxSize>
inline ArrayList<T, maxSize>::ArrayList()
: contents(), count(0)
{
	for (int i = 0; i < maxSize; i++) {
		contents[i] = NULL;
	}
}

template<class T, int maxSize>
inline ArrayList<T, maxSize>::~ArrayList()
{
}

template<class T, int maxSize>
inline int ArrayList<T, maxSize>::add(T* obj) {
	if (count < maxSize) {
		contents[count] = obj;
	}
	return count++;
	// hey jf - this just silently fails if the list is full.
}

template<class T, int maxSize>
inline int ArrayList<T, maxSize>::remove(T* obj) {
	for (int i = 0; i < count; i++) {
		if (contents[i] == obj) {
			remove(i);
			return i;
		}
	}
	return -1;
}

template<class T, int maxSize>
inline void ArrayList<T, maxSize>::remove(int ndx) {
	contents[ndx] = contents[count - 1];
	contents[count - 1] = NULL;
	count--;
}

template<class T, int maxSize>
inline bool ArrayList<T, maxSize>::contains(T* obj) {
	return indexOf(obj) != -1;
}

template<class T, int maxSize>
inline int ArrayList<T, maxSize>::indexOf(T* obj) {
	for (int i = 0; i < count; i++) {
		if (contents[i] == obj) {
			return i;
		}
	}
	return -1;
}

template<class T, int maxSize>
inline int ArrayList<T, maxSize>::size() {
	return count;
}

template<class T, int maxSize>
inline T ArrayList<T, maxSize>::operator [](int ndx) const {
	return contents[ndx];
}

} /* namespace us_cownet_util */

#endif /* ARRAYLIST_H_ */
