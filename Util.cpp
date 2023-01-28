#pragma once
#include "Util.h"
#include <cmath>
//template <typename T>T sum(::vector<T> nums);
//template <typename T>T sum(::vector<T> nums);}
namespace std
{

    vector<string> stringToList(string str, char sep, bool greedy) {
        // greedy means treating consecutive seprators as one separator while non greedy treats each separtor as one separtor
        vector<string> strList;
        string word = "";
        for (int i = 0; i < str.size(); i++) {
            char c = str[i];
            if (c == sep) {
                if (greedy && word != "") strList.push_back(word);
                else if (!greedy) strList.push_back(word);
                word = "";
                continue;
            }
            word += c;
            if(i == str.size() - 1) 
                strList.push_back(word);
        }
        return strList;
    }

    int nextPrime(int num) {
        while (true) {
            if (isPrime(++num)) return num;
        }
    }
    bool isPrime(int num) {
        for (int i = 2; i < floor(sqrt(num)); i++)
            if (num % i == 0) return false;
        return true;
    }
}

