#include "Compressor.h"
using namespace std;
Compressor::Compressor(string str):str(str){}
void Compressor::setStr(string s) { str = s; }
/*
the output is an encoder of type dict<char>
this function encodes the most freqeunt word (according to size bytes) in the string with all unused characters
first key in the encoder is marked as a special charcter to be used in decoding (thus not used in encoding)
*/
Dict<char> Compressor::encodeFrequentWords(CharFrequencyTable cft, WordFrequencyTable wft) {
    vector<unsigned char> unusedChar = cft.getUnusedChar();
    Dict<int> spw = wft.getSizePerWord();
    spw.sort();
    // spw.print();
    Dict<char> encodedWords;
    int wordCount = spw.size();
    vector<string> words = spw.getKeys();
    encodedWords.append(string(1, unusedChar[0]), unusedChar[0]);
    //special character to be used in compression and decompression
    for (int i = 0; i < unusedChar.size() - 1; i++) {
        if (i >= wordCount) break;
        if (wft.get(words[i], 0) <= 1) continue;
        encodedWords.append(words[i], unusedChar[i + 1]);
    }
    return encodedWords;
}
// adds header at the begining ofthe string containing all the encoder key-value pairs
// compresses a string by replacing each word in encoder with respective unused character
string Compressor::compress(Dict<char> encoder, string str) {
    string compStr = "";
    vector<string> words = encoder.getKeys();
    vector<char> chars = encoder.getValues();
    // first character in encoder is special character
    string special_char = string(1, chars[0]);
    // add special character at the begining for the decoder to know it
    compStr += special_char;
    // add every word followed by the special character foolowed by unused character in header
    for (int i = 1; i < words.size(); i++) {
        char c = chars[i];
        compStr += words[i] + special_char + c;
    }
    // add two consecutive special characters to end the header
    compStr += special_char + special_char;
    // add compressed string
    compStr += Dict<char>::replace(str, encoder);
    return compStr;
}
// marks first character as special and build decoder untill two spceial are encountered
// then start decoding the document and return it without header (decoder)
string Compressor::decompress() {
    char special_char = str[0];
    Dict<string> decoder;
    string word = "";
    int header_idx = 0;
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == special_char && str[i + 1] == special_char) {
            header_idx = i + 2;
            break;
        }
        if (str[i] != special_char) {
            word += str[i];
        }
        else if (str[i] == special_char) {
            string s = string(1, str[i + 1]);
            decoder.set(s, word);
            word = "";
            i++;
        }
    }
    //decoder.print();
    return Dict<string>::replace(str.substr(header_idx), decoder);
}
// compress a string 
string Compressor::compress() {
    // first building string word frequency and character frequency 
    WordFrequencyTable wordFreqTable(str);
    CharFrequencyTable charFreqTable(str);
    // second build encoder
    Dict<char> encodedWords = encodeFrequentWords(charFreqTable, wordFreqTable);
    // lastly compress string using encoder
    string comp_str = compress(encodedWords, str);
    return comp_str;
}
