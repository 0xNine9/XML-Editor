#pragma once
#include <vector>
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

	void decompress_file(string file_name);
	void compress_file(string file_name);
}
