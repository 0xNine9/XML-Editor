#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include<sstream>
#include<string>
#include "Dict.h"
#include "Util.h"
#include "CharFrequencyTable.h"
#include "WordFrequencyTable.h"
namespace std
{
	Dict<char> encodeFrequentWords(CharFrequencyTable cft, WordFrequencyTable wft);
	string decompress(string str);
	string compress(Dict<char> encoder, string str);
	void writeFileBytes(const string& fileName, const string& content);
	string readFileBytes(const string& fileName);
	void decompress_file(string file_name);
	void compress_file(string file_name);
}
