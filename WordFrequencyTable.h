#pragma once
#include "FrequencyTable.h"
namespace std {
	class WordFrequencyTable :public FrequencyTable
	{
	private:
		void setFreqTable(char sep);
	public:
		WordFrequencyTable();
		WordFrequencyTable(string str);
		WordFrequencyTable(string str, char sep);
		Dict<int> getSizePerWord();
	};
}

