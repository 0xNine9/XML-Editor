#include "Compression.h"

namespace std {
    Dict<char> encodeFrequentWords(CharFrequencyTable cft, WordFrequencyTable wft) {
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
            if (i == 30) {
                cout << words[i];
            }
            if (i >= wordCount) break;
            if (wft.get(words[i], 0) <= 1) continue;
            encodedWords.append(words[i], unusedChar[i + 1]);
        }
        return encodedWords;
    }
    string readFileBytes(const string& fileName) {
        ifstream file(fileName, ios::binary);
        string fileContent;
        char buffer;
        while (file.read(&buffer, sizeof(buffer))) {
            fileContent.push_back(buffer);
        }
        return fileContent;
    }
    void writeFileBytes(const string& fileName, const string& content) {
        ofstream file(fileName, ios::binary);
        for (unsigned char ch : content) {
            file.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
        }
        file.close();
    }
    string decompress(string str) {
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
    string compress(Dict<char> encoder, string str) {
        string compStr = "";
        vector<string> words = encoder.getKeys();
        vector<char> chars = encoder.getValues();
        string special_char = string(1, chars[0]);
        compStr += special_char;
        for (int i = 1; i < words.size(); i++) {
            char c = chars[i];
            compStr += words[i] + special_char + c;
        }
        compStr += special_char + special_char;
        compStr += Dict<char>::replace(str, encoder);
        return compStr;
    }
    void decompress_file(string file_name) {
        string str = readFileBytes(file_name);
        string decomp_str = decompress(str);
        writeFileBytes("Decompressed_" + file_name, decomp_str);
    }
    void compress_file(string file_name) {
        string str = readFileBytes(file_name);
        WordFrequencyTable wordFreqTable(str);
        CharFrequencyTable charFreqTable(str);
        Dict<char> encodedWords = encodeFrequentWords(charFreqTable, wordFreqTable);
        string comp_str = compress(encodedWords, str);
        writeFileBytes("Compressed_" + file_name, comp_str);
    }

}