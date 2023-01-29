#ifndef CONVERT_H_
#define CONVERT_H_

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

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


string readFileIntoString(const string& path);
Node* Parse_XML(const string XML_content);
string convert_json(Node* node, int level = 1);
void Free_XML(Node* root);
string insert_taps(int level);
string erase_unwanted_chars(string str);


#endif // !
