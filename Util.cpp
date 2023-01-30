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
    string insert_taps(int level) {
        string taps = "";
        for (int i = 0; i < level; i++) {
            taps += "\t";
        }
        return taps;
    }
    string erase_unwanted_chars(string str) {
        vector<char> sequences = { '\a','\b','\r','\n','\v','\t' };
        for (int i = 0; i < str.length(); ++i) {
            for (char seq : sequences) {
                if (str[i] == seq) {
                    str.erase(i, 1);
                    while (str[i] == ' ' && (str[i + 1] == ' ')) {
                        str.erase(i, 2);
                    }
                    i--;
                    break;
                }
            }
        }
        return str;
    }
    string format_newLine(string str, int level, int maxChar) {
        string new_str = "";
        for (int i = 0; i < str.length(); ++i) {
            if ((i+1) % maxChar != 0) new_str += str[i];
            else {
                int j = 20;
                while(str[i] != ' ' && j !=0){
                    new_str += str[i];
                    i++;
                    j--;
                    if (i == str.length() - 1) break;
                }
                new_str += "\n" + insert_taps(level) + str[i];
            }
        }
        return new_str;
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

