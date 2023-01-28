#pragma once
#include <vector>
#include <string>
//#include "Dict.h"
//template <typename T>T sum(std::vector<T> nums);
//template <typename T>T sum(std::vector<T> nums);}
namespace std
{

    template <typename T>T sum(std::vector<T> nums) {
        T sum = 0;
        for (T num : nums)
        {
            sum += num;
        }
        return sum;
    }
    vector<string> stringToList(string str, char sep = ' ',bool greedy = true);
    //string replace(string str, Dict<char> dict,char sep = ' ');
    int nextPrime(int num);
    bool isPrime(int num);
}
