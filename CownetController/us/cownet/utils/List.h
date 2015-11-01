/*
 * List.h
 *
 *  Created on: Oct 14, 2015
 *      Author: jfitzpatrick
 */

#ifndef LIST_H_
#define LIST_H_

namespace us_cownet_utils {

template <class T, int maxSize>
class List {
public:
	List();
	virtual ~List();

	void add(T object);
	void remove(T object);
	void removeNdx(int ndx);
	void clear();
	int size() const;
	T operator[](int ndx);
	int indexOf(T object);

private:
	int currentSize;
	T values[maxSize];
};

template<class T, int maxSize>
inline us_cownet_utils::List<T, maxSize>::List()
: currentSize(0)
{
}

template<class T, int maxSize>
inline us_cownet_utils::List<T, maxSize>::~List() {
}

template<class T, int maxSize>
inline void us_cownet_utils::List<T, maxSize>::add(T object) {
	values[currentSize++] = object;
}

template<class T, int maxSize>
inline void us_cownet_utils::List<T, maxSize>::remove(T object) {
	int ndx = indexOf(object);
	if (ndx != -1) {
		removeNdx(ndx);
	}
}

template<class T, int maxSize>
inline void us_cownet_utils::List<T, maxSize>::removeNdx(int ndx) {
	currentSize--;
	values[ndx] = values[currentSize];
}

template<class T, int maxSize>
inline void us_cownet_utils::List<T, maxSize>::clear() {
	currentSize = 0;
}

template<class T, int maxSize>
inline int us_cownet_utils::List<T, maxSize>::size() const {
	return currentSize;
}

template<class T, int maxSize>
inline T us_cownet_utils::List<T, maxSize>::operator [](int ndx) {
	return values[ndx];
}

template<class T, int maxSize>
inline int us_cownet_utils::List<T, maxSize>::indexOf(T object) {
	for (int i = 0; i < currentSize; i++) {
		if (values[i] == object) {
			return i;
		}
	}
	return -1;
}

} /* namespace us_cownet_utils */

#endif /* LIST_H_ */
