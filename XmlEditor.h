#pragma once
#include "tree.h"
#include "SString.h"
#include "Compressor.h"
#include <functional>
#include <string>
#include <list>
#include <iterator>
namespace std{
class XmlEditor
{
private:
	string str;
	string original_text;
	string current_text;
	Node* tree;
	string errors_detected;
	Compressor compressor;
	void update_attributes();
	string minify(Node* node);
	string prettify(Node* node,int level = 1);
    bool are_children_same(Node* node);
    string convert_json(Node* node, int level = 1, bool isList = false, int idx =0);
	void update_ins_offset(vector<pair<int, int>>& ins_off_pair_list, int& insertion_idx, int length);
public:
	//Compressor compressor;
	XmlEditor(string xml_text = "");
	string get_current_text();
    void set_current_text(string str);
	string get_original_text();
	Node* get_tree();
	string get_errors();
	void compress();
	void decompress();
	void Xml_parse();
	void prettify();
	void minify();
	void convert_json();
	void validate();
};
}

