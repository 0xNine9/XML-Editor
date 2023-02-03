/*#include "Dict.h"
#include <iostream>
using namespace std;
template <class T> int Dict<T>::findKeyIndex(string key) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) return i;
	}
	return -1;
}
template <class T> Dict<T>::Dict<T>() {}
template <class T> bool Dict<T>::contain(string key) {
	return findKeyIndex(key) != -1;
}
template <class T> void Dict<T>::append(string key, int value) {
	if (!contain(key)) {
		keys.push_back(key);
		values.push_back(value);
	}
}
template <class T> T Dict<T>::get(string key, T def_val) {
	int index = findKeyIndex(key);
	if (index != -1)
		return values.at(index);
	else {
		append(key, def_val);
		return def_val;
	}
}
template <class T> int Dict<T>::size() { return keys.size(); }
template <class T> void  Dict<T>::set(string key, T val) {
	int index = findKeyIndex(key);
	if (index != -1)
		values[index] = val;
	else {
		append(key, val);
	}
}
template <class T> void Dict<T>::print() {
	for (int i = 0; i < keys.size(); i++)
	{
		cout << keys[i] << "\t" << values[i] << "\n";
	}
}
template <class T> vector<string>  Dict<T>::getKeys() { return keys; }
template <class T> vector<T> Dict<T>::getValues() { return values; }
template <class T> void Dict<T>::sort() {
	for (int i = 0; i < values.size(); i++) {
		for (int j = 0; j < values.size(); j++) {
			if (values[i] > values[j]) {
				swap(values[i], values[j]);
				swap(keys[i], keys[j]);
			}
		}

	}
}

void TempDicwt()
{
	Dict<int> t1;
	Dict<char> t2;
	Dict<string> t3;
}*/
