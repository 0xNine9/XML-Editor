#pragma once
#include <string>
#include <fstream>

namespace std{
class FileHandler
{
public:
        static void writeFileBytes(const string& fileName, const string& content);
        static string readFileBytes(const string& fileName);
};
}

