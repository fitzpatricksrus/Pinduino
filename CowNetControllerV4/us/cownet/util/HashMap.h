/*
 * HashMap.h
 *
 *  Created on: Jul 28, 2015
 *      Author: jfitzpatrick
 */

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <stddef.h>

namespace us_cownet_util {

template <class Key, class Value, int maxSize> class HashMap {
public:
	typedef int HashFunction(Key key);

	HashMap(HashFunction* hash);
	~HashMap();

	Value* get(Key key) const;
	void put(Key key, Value* value);
	void remove(Key key);
	Key* keySet();

private:
	int getNdx(Key key) const;

	HashFunction* hash;
	bool isFree[maxSize];
	Key keys[maxSize];
	Value* values[maxSize];
};

template<class Key, class Value, int maxSize>
inline HashMap<Key, Value, maxSize>::HashMap(HashFunction* hashIn)
: hash(hashIn), isFree(), keys(), values()
{
	for (int i = 0; i < maxSize; i++) {
		isFree[i] = true;
	}
}

template<class Key, class Value, int maxSize>
inline HashMap<Key, Value, maxSize>::~HashMap() {
}

template<class Key, class Value, int maxSize>
inline Value* HashMap<Key, Value, maxSize>::get(Key key) const {
	int h = ((*hash)(key)) % maxSize;
	for (int i = 0; i < maxSize; i++) {
		int ndx = (i + h) % maxSize;
		if (keys[ndx] == key) {
			return values[ndx];
		}
	}
	return NULL;
}

template<class Key, class Value, int maxSize>
inline void HashMap<Key, Value, maxSize>::put(Key key, Value* value) {
	if (value == NULL) {
		remove(key);
	} else {
		int h = ((*hash)(key)) % maxSize;
		for (int i = 0; i < maxSize; i++) {
			int ndx = (i + h) % maxSize;
			if (isFree[ndx] || keys[ndx] == key) {
				keys[ndx] = key;
				values[ndx] = value;
				isFree = false;
				return;
			}
		}
		// hey jf - this just silently fails when full
	}
}

template<class Key, class Value, int maxSize>
inline void HashMap<Key, Value, maxSize>::remove(Key key) {
	int ndx = getNdx(key);
	while (ndx != -1) {
		keys[ndx].isFree = true;
		values[ndx] = NULL;
		// is there a way to clear the key?
		ndx = getNdx(key);
	}
}

template<class Key, class Value, int maxSize>
inline Key* HashMap<Key, Value, maxSize>::keySet() {
	return keys;
}

template<class Key, class Value, int maxSize>
inline int HashMap<Key, Value, maxSize>::getNdx(Key key) const {
	int h = ((*hash)(key)) % maxSize;
	for (int i = 0; i < maxSize; i++) {
		int ndx = (i + h) % maxSize;
		if (keys[ndx] == key) {
			return ndx;
		}
	}
	return -1;
}

} /* namespace us_cownet_util */


#endif /* HASHMAP_H_ */
