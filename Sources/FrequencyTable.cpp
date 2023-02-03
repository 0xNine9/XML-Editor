#include "FrequencyTable.h"

using namespace std;
FrequencyTable::FrequencyTable() {
    this->str = "";
}
FrequencyTable::FrequencyTable(string str): Dict() {
    this->str = str;
}
