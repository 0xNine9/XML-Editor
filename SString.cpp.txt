#include "SString.h"
using namespace std;
// convert string to list separated by separator 
// greedy means treating consecutive seprators as one separator while non greedy treats each separtor as one separtor
vector<string> SString::stringToList(string str, char sep, bool greedy) {
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
        if (i == str.size() - 1)
            strList.push_back(word);
    }
    return strList;
}
// insert tabs n times where n =level
string SString::insert_taps(int level) {
    string taps = "";
    for (int i = 0; i < level; i++) {
        taps += "\t";
    }
    return taps;
}
// erase escape character sequence and extra white space if specified 
string SString::erase_unwanted_chars(string str, bool erase_white_space) {
    vector<char> sequences = { '\a','\b','\r','\n','\v','\t' };
    for (int i = 0; i < str.length(); ++i) {
        for (char seq : sequences) {
            if (erase_white_space) {
                while (str[i] == ' ' && (str[i + 1] == ' ')) {
                    str.erase(i, 2);
                }
            }
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
// limit each line to certain number of characters with an additional 20 characters for last word
string SString::format_newLine(string str, int level, int maxChar) {
    string new_str = "";
    for (int i = 0; i < str.length(); ++i) {
        if ((i + 1) % maxChar != 0) new_str += str[i];
        else {
            int j = 20;
            while (str[i] != ' ' && j != 0) {
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
