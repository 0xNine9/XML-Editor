#include "CharFrequencyTable.h"
using namespace std;
CharFrequencyTable::CharFrequencyTable(string str) {
    this->str = str;
    setFreqTable(1);
}
CharFrequencyTable::CharFrequencyTable(string str,int n_grams): FrequencyTable(str) {
    setFreqTable(n_grams);
}
void CharFrequencyTable::setFreqTable(int n_grams) {
        //    create frequency table for each n_grams char sequence (default is single character)
    if (n_grams == 1) {
        int charFreq[255] = { 0 };
        for (unsigned char c : str) {
            int i = int(c);
            charFreq[i] += 1;
        }
        for (int i = 0; i < 256; i++) {
            if (charFreq[i] > 0) {
                char c = i;
                string s = string(1,c);
                set(s, charFreq[i]);
            }
        }
        }
    else {
        int counter = 0;
        string chr = "";
        for (int i = n_grams; i < str.size() + n_grams; i++) {
            chr = "";
            for (int j = n_grams; j > 0; j--)
            {
                chr += str[i - j];
            }
            counter = get(chr, 0);
            set(chr, counter + 1);
            cout << i << "\n";
        }
    }
}
vector<unsigned char> CharFrequencyTable::getUnusedChar() {
    // to be used ONLY with single character frequency table otherwise it isn't usable 
    vector<unsigned char> unusedChar;
    string chr = "";
    int counter = 0;
    for (int i = 1; i < 256; i++) {
        char c = i;
        chr = c;
        // convert number to character (for all 8-bit ascii characters except null character) 
        // then conver it to string for function argument
        if (contain(chr)) continue;
        counter++;
        unusedChar.push_back(c);
    }
    cout << counter;
    return unusedChar;
}