#pragma once
#include <string>
#include <vector>
namespace std {
    class SString
    {
    public:
        static vector<string> stringToList(string str, char sep = ' ', bool greedy = true);
        static string erase_unwanted_chars(string str, bool erase_white_space = false);
        static string format_newLine(string str, int level, int maxChar = 50);
        static string insert_taps(int level);
    };
}

