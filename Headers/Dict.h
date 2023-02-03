#pragma once
#include<string>
#include<iostream>
#include<vector>
#include "SString.h"
namespace std {
	template <class T> class Dict {
	protected:
		vector<string> keys;
		vector<T> values;
		int findKeyIndex(string key);
	public:
		Dict();
		bool contain(string key);
		void append(string key, T value = 1);
		T get(string key, T def_val = 1);
		int size();
		void set(string key, T val);
		void print();
		vector<string> getKeys();
		vector<T> getValues();
		void sort();
		static string replace(string str, Dict<char> dict, char sep=' ');
		static string replace(string str, Dict<string> dict, char sep = ' ');
	};
    template <class T> Dict<T>::Dict(){}
	template <class T> string Dict<T>::replace(string str, Dict<char> dict, char sep) {
		string replacedStr = (str[0] == sep) ? string(1, sep) : "";
		// if seprator is first character in the string add it otherwise assign to null
		vector<string> strList = SString::stringToList(str, sep, false);
		for (int i = 0; i < strList.size(); i++) {
			string word = strList[i];
			if (dict.contain(word)) replacedStr += dict.get(word);
			else replacedStr += word;
			replacedStr += sep;
		}
		return replacedStr;
	}
		template <class T> string Dict<T>::replace(string str, Dict<string> dict, char sep) {
		string replacedStr = (str[0] == sep) ? string(1, sep) : "";
		// if seprator is first character in the string add it otherwise assign to null
		vector<string> strList = SString::stringToList(str, sep, false);
		for (int i = 0; i < strList.size(); i++) {
			string word = strList[i];
			if (dict.contain(word)) replacedStr += dict.get(word,"");
			else replacedStr += word;
			if (i < strList.size() - 1) replacedStr += sep;
		}
		return replacedStr;
	}
	template <class T> int Dict<T>::findKeyIndex(string key) {
			for (int i = 0; i < keys.size(); i++) {
				if (keys[i] == key) return i;
			}
			return -1;
	}
	template <class T> bool Dict<T>::contain(string key) {
		return findKeyIndex(key) != -1;
	}
	template <class T> void Dict<T>::append(string key, T value) {
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
}
