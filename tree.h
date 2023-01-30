#pragma once

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "Util.h"
//string json_text;

class Node {
public:
	string TagName;
	string TagValue;
	Node* parent;
	vector<Node*> children;

	Node(string tagval = "", string textval = "", Node* p = NULL) :TagName{ tagval }, TagValue{ textval }, parent{ p } {}

	// Making sure that the allocated nodes are being destructed correctly
	~Node() {
		// cout << "destructor"<<endl;
	}
};
Node* Parse_XML(const string XML_content);
void Free_XML(Node* root);

