#include "WordFrequencyTable.h"
#include "Util.h"
using namespace std;
WordFrequencyTable::WordFrequencyTable() {
    this->str = "";
    setFreqTable(1);
}
WordFrequencyTable::WordFrequencyTable(string str):FrequencyTable(str) {
    setFreqTable(' ');
}
WordFrequencyTable::WordFrequencyTable(string str, char sep):FrequencyTable(str) {
    setFreqTable(sep);
}
void WordFrequencyTable::setFreqTable(char sep) {
    //create frequency table for each word separted by sep (default is " ")

    vector<string> strList = stringToList(str, sep);
    int counter = 0;
    for (int i = 0; i < strList.size(); i++) {
        counter = get(strList[i], 0);
        set(strList[i], counter + 1);
        //cout << i<<"\n";
    }

}
Dict<int> WordFrequencyTable::getSizePerWord() {
    Dict<int> spw;
    for (int i = 0; i < keys.size(); i++) {
        int size = keys[i].size();
        int new_val = size * values[i];
        spw.append(keys[i], new_val);
    }
    return spw;
}