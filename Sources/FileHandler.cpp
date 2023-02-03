#include "FileHandler.h"
using namespace std;
string FileHandler::readFileBytes(const string& fileName) {
    ifstream file(fileName, ios::binary);
    string fileContent;
    char buffer;
    while (file.read(&buffer, sizeof(buffer))) {
        fileContent.push_back(buffer);
    }
    return fileContent;
}
void FileHandler::writeFileBytes(const string& fileName, const string& content) {
    ofstream file(fileName, ios::binary);
    for (unsigned char ch : content) {
        file.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
    }
    file.close();
}