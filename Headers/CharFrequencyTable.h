#pragma once
#include "FrequencyTable.h"
namespace std {
	class CharFrequencyTable :public FrequencyTable
	{
	private:
		void setFreqTable(int n_grams);
	public:
		CharFrequencyTable(string str);
		CharFrequencyTable(string str, int n_grams);
		vector<unsigned char> getUnusedChar();
	};
}

