#pragma once
#include "Dict.h"
#include "CharFrequencyTable.h"
#include "WordFrequencyTable.h"
#include <string>
#include <vector>
namespace std {
class Compressor
{
private:
	string compress(Dict<char> encoder, string str);
	Dict<char> encodeFrequentWords(CharFrequencyTable cft, WordFrequencyTable wft);
public:
	string str;
	Compressor(string str);
	string compress();
	string decompress();
	void setStr(string str);
};
}

