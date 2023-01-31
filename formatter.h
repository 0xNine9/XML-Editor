#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include "tree.h"
#include "Util.h"
namespace std {
    string minify(Node* node);
    string prettify(Node* node, int level = 0);
    string convert_json(Node* node, int level = 1);
    string validate(string xml_text);
}


