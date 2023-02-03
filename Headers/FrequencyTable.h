#pragma once
#include<string>
#include<vector>
#include "Dict.h"
namespace std {
    class FrequencyTable : public Dict<int>
    {
    protected:
        string str;
        FrequencyTable();
        FrequencyTable(string str);
        //virtual ~FrequencyTable() = 0;
    };
}

