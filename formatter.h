#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <vector>
#include <stack>
#include "tree.h"
#include "Util.h"
namespace std {
	string prettify(const char* s);
	string minify(Node* node);
	string convert_json(Node* node, int level = 1);
}


