#include "FrequencyTable.h"
#include "Util.h"
#include "CharFrequencyTable.h"
using namespace std;
FrequencyTable::FrequencyTable() {
    this->str = "";
}
FrequencyTable::FrequencyTable(string str): Dict() {
    this->str = str;
}
vector<float>  FrequencyTable::generateFrequencyFractions() {
    vector<float> fractions;
    int totalCount = sum(values);
    for (float val : values) { fractions.push_back(100 * (val / totalCount)); }
    return fractions;
}
