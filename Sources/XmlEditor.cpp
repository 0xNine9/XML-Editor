#include "XmlEditor.h"
using namespace std;
// constructor that initialize all attributes 
XmlEditor::XmlEditor(string xml_text) : current_text(xml_text), compressor(current_text) {
    errors_detected = " Validate xml to check for errors first";
    original_text = current_text;
};
// getters and setters for attributes
string XmlEditor::get_current_text() { return current_text; };
void XmlEditor::set_current_text(string str){current_text = str;
                                                update_attributes();}
string XmlEditor::get_original_text() { return original_text; };
string XmlEditor::get_errors() { return errors_detected; };
Node* XmlEditor::get_tree() { return tree; };
// convert xml file to xml tree
void XmlEditor::Xml_parse() { tree = Node::Parse_XML(current_text); };
// update original text and compressor string 
void XmlEditor::update_attributes() {
    // if original text is empty set it to current string otherwise leave it as it is
    original_text = (original_text.compare("") == 0) ? current_text : original_text;
    compressor.setStr(current_text);
}
// compress current text in xml editor
void XmlEditor::compress() {
    current_text = compressor.compress();
    update_attributes();
}
// decompress current text in xml editor
void XmlEditor::decompress() {
    current_text = compressor.decompress();
    update_attributes();
}
// prettify current text in xml editor
void XmlEditor::prettify() { 
	tree = Node::Parse_XML(current_text); 
	current_text = prettify(tree);
    update_attributes();
};
// remove all extra spaces and add indentation and extra lines as needed to make xml look clean
string XmlEditor::prettify(Node* node, int level) {
    // insert appropriate taps and write tag name
    string prettified_xml = SString::insert_taps(level) + "<" + node->TagName + ">";
    for (int i = 0; i < node->children.size(); i++) {
        // add newline and recursively call the function untill leaf node (dfs)
        prettified_xml += "\n";
        prettified_xml += prettify(node->children[i], level + 1);
    }
    // write value of tag but with maximum characters for each line for improved visualisation
    // close the tag afterwards
    string tag_value = SString::format_newLine(SString::erase_unwanted_chars(node->TagValue), level);
    if (tag_value.length() >= 75) prettified_xml += "\n" + SString::insert_taps(level) + tag_value + "\n" + SString::insert_taps(level) + "</" + node->TagName + ">";
    else if (node->children.size() > 0) prettified_xml += "\n" + SString::insert_taps(level) + tag_value + "</" + node->TagName + ">";
    else prettified_xml += tag_value + "</" + node->TagName + ">";
    //minified_xml += "\n";
    return prettified_xml;
};
// minify current text in xml editor
void XmlEditor::minify() {
    tree = Node::Parse_XML(current_text);
    current_text = minify(tree);
    update_attributes();
};
// remove all extra spaces and newline characters
string XmlEditor::minify(Node* node) {
    // add appropriate tag name
    string minified_xml = "<" + node->TagName + ">";
    for (int i = 0; i < node->children.size(); i++) {
        // recursively call the function untill leaf node (dfs)
        minified_xml += minify(node->children[i]);
    }
    // erase all unwanted characters from value
    minified_xml += SString::erase_unwanted_chars(node->TagValue) + "</" + node->TagName + ">";
    return minified_xml;
};
// convert current text in xml editor to json format
void XmlEditor::convert_json() {
    tree = Node::Parse_XML(current_text);
    current_text = "{" + convert_json(tree) + "\n}";
    update_attributes();
};
// check if all node children have the same tag name 
bool XmlEditor::are_children_same(Node* node) {
    if (node->children.size() < 2) return false;
    for (int i = 0; i < node->children.size()-1; i++) {
        Node* current_child = node->children[i];
        Node* next_child = node->children[i+1];
        if (current_child == NULL || next_child == NULL) return false;
        if (current_child->TagName.compare(next_child->TagName) != 0) return false;
    }
    return true;
}
/* converts xml tree to json string
* node and level are tree node and level in tree
* isList is a boolean variable to indicate if the current node is part of a Json list or not
* idx is an integer to indicate the current child node position
* */
string XmlEditor::convert_json(Node* node, int level,bool isList,int idx) {
    string json = "";
    // if tag isn't in a json list  add appropriate space and write tag name
    if (!isList) {
        json += "\n" + SString::insert_taps(level) + "\"" + node->TagName + "\": ";
    }
    // if it is in a Json list add appropriate space 
    else {
        json += "\n" + SString::insert_taps(level);
        // if it is the first child write its tag name
        if (idx == 0) {
            json += "\"" + node->TagName + "\": [\n" + SString::insert_taps(level);
        }
        // if it is not the first child and has children itself add {
        else if(idx >0 && node->children.size() > 0)
        json +=  "{";
    }
    // if tag has children and all its children names are the same
    if (node->children.size() > 1 && are_children_same(node)) {
        // add { if tag is in a list and not the first index
        json += (isList && idx !=0)? "" : "{";
        // set its children to be in a list
        isList = true;
    }
    else if (node->children.size() > 0 && !are_children_same(node)) {
        // add { if tag is in a list and not the first index
        json += (isList && idx!=0) ? "" : "{";
        // set its children not to be in a list
        isList = false;
    }
    // if it is a leaf node (only has value) then add its value with the appropriate spacing
    else if (node->children.size() == 0) {
        json += "\"" + SString::format_newLine(SString::erase_unwanted_chars(node->TagValue), level) + "\"";
        isList = false;
    }
    // recursivly loop over children
    for (int i = 0; i < node->children.size(); i++) {
        json += convert_json(node->children[i], level + 1,isList,i) ;
        // add comma between children except the last one
        json = (i < node->children.size() - 1) ? json + "," : json;
    }
    // if the json list ended close it appropriately 
    if (isList) json += "\n" + SString::insert_taps(level) + "]" + "\n" + SString::insert_taps(level-1) + "}";
    // if there were more than one child then close it appropriately 
    else if (node->children.size() > 0) json += "\n" + SString::insert_taps(level) + "}";
    return json;
};
/*
this function corrects the insertion positions and updates the insertion offset pair_list:
1) if current insertion index is smaller than or equal previous insertion index don't add offset
2) if current insertion index is bigger than previous insertion index add offset
after that update insertion offset parilist with the current insertion and tag length
*/
void XmlEditor::update_ins_offset(vector<pair<int, int>>& ins_off_pair_list, int& insertion_idx, int length) {
    int ins_off = 0;
    for (pair<int, int> idxOff : ins_off_pair_list) {
        if (idxOff.first < insertion_idx) ins_off += idxOff.second;
    }
    ins_off_pair_list.push_back(make_pair(insertion_idx, length));
    insertion_idx += ins_off;
}
/*
The function is splitted into 4 stages:
1) Initialize opened tags and closed tags LinkedLists of <int,string> pair (explained inside function)
2) Detect closing tags that weren't opened or opening tags taht weren't closed
3) correct those errors by insertion in the string at an estimated correct position
4) clean extra tags at the begining or the ending of the string
Note that stage 2,3 are done at the same iteration but other stages are separate
*/
void XmlEditor::validate() {
    // Initialsign variables
    string xml = current_text;
    string validated_xml = xml;
    string detected_errors = "";
    string tag = "";
    // linked list of pairs for closed tags and opened tags
    // first is index position exactly after the end of tag
    // second is the tag name itself "<tag>" without attributes
    list<pair<int, string>> opened_tags;
    list<pair<int, string>> closed_tags;
    // dynamic array of pair of intgers
    // first is the insertion index of the corrected tag
    // second is the tag length itself
    vector<pair<int, int>> ins_off_pair_list;
    // bool to indicate opening tags are looped through entirely
    bool isFinishied = false;
    // Stage 1: Initialising opened tags, closed tags
    for (int i = 0; i < xml.length(); i++) {
        // if it begins with < then it is a tag otherwise it is a value
        if (xml[i] == '<') {
            while (xml[i] != '>') {
                tag += xml[i];
                i++;
            }
            // to add the last '>'
            tag += xml[i];
            // erase extra spcaes and escape characters
            tag = SString::erase_unwanted_chars(tag, true);
            // add index,name pair for every list correctly while ignoring self-closing tags
            if ((tag[1] != '/') && tag[tag.length() - 2] != '/') opened_tags.push_back(make_pair(i, tag));
            else if ((tag[1] == '/') && tag[tag.length() - 2] != '/') {
                closed_tags.push_back(make_pair(i, tag));
            }
            tag = "";
        }
    }
    // Stage 2 and 3 : error detection and correction
    // looping over closed tags
    while (closed_tags.size() > 0) {
        // if there are no more oepning tags exit or opening tags have been completely looped through
        if (opened_tags.size() == 0 || isFinishied)
            break;
        // get closing tag index and tagName
        string closing_tag = closed_tags.front().second;
        int closing_tag_idx = closed_tags.front().first;
        cout << closing_tag_idx << "\n";
        // iterator for opened tags
        list<pair<int, string>>::iterator it = opened_tags.begin();
        // iterate on all opening tags
        while (opened_tags.size() > 0) {
            // get opening tag index and tagName without attributes
            int opening_tag_idx = (*it).first;
            string opening_tag = SString::stringToList((*it).second)[0];
            // make sure it ends in ">" since attributes won't have that when slicing
            opening_tag = (opening_tag[opening_tag.length() - 1] == '>') ? opening_tag : opening_tag + '>';
            // detect opening and closing errors with correction
            {
                string tmp_closing_tag = closing_tag;
                //check if opening came after closing  (Missing opening tag)
                if (closing_tag_idx < opening_tag_idx) {                    
                    // if the first tag is missing insert at the begining
                    int insertion_idx = 0;
                    list<pair<int, string>>::iterator it2 = opened_tags.begin();
                    // otherwise insert just after the closest opening tag before closing tag
                    for (int i = 0; i < opened_tags.size(); i++) {
                        string next_opening_tag = (*it2).second;
                        int next_opening_tag_idx = (*it2).first;
                        if (next_opening_tag_idx > closing_tag_idx) break;
                        insertion_idx = next_opening_tag_idx + 1;
                        advance(it2, 1);
                    }
                    // The opening tag is just the opening after erasing '/' 
                    string correct_opening = tmp_closing_tag.erase(1, 1);
                    // correct insertion index and update insertion offset array
                    update_ins_offset(ins_off_pair_list, insertion_idx, correct_opening.length());
                    // insert corrected tag at estimated position
                    validated_xml.insert(insertion_idx, correct_opening);
                    // add respective error message
                    detected_errors += "Missing Opening Tag\t" + closing_tag + " at position: " + to_string(insertion_idx) + "\n";
                    // remove first closed tag from linked list
                    closed_tags.pop_front();
                    // go to next closed tag and repeat 
                    break;
                }
                // if both tag names are the same
                else if (opening_tag.compare(tmp_closing_tag.erase(1, 1)) == 0) {
                    // if last tag is reached erase both closing and opening and exit the loop
                    if (opening_tag_idx == opened_tags.back().first) {
                        closed_tags.pop_front();
                        opened_tags.erase(it);
                        break;
                    }
                    // check that this is the correctly matched opening tag (the nearest one)
                    // create new iterator to check
                    list<pair<int, string>>::iterator it2 = it;
                    int next_opening_tag_idx = 0;
                    do {
                        advance(it2, 1);
                        // if opened tags are finished exit
                        if (it2 == opened_tags.end()) break;
                        string next_opening_tag = (*it2).second;
                        next_opening_tag_idx = (*it2).first;
                        if (next_opening_tag.compare(tmp_closing_tag) == 0 && next_opening_tag_idx < closing_tag_idx) {
                            it = it2;
                        }
                    } while (closing_tag_idx > next_opening_tag_idx);
                    // assign  new iterator to correct opening tag
                    it2 = it;
                    // else check if there are any opening tags between opening and closing (Missing closing tag)
                    do {
                        advance(it2, 1);
                        // if opened tags are finished exit
                        if (it2 == opened_tags.end()) break;
                        opening_tag_idx = (*it2).first;
                        // if there are any tags it means it is opened but not closed
                        if (closing_tag_idx >= opening_tag_idx) {
                            // closing tag is inserted just before the current closing tag
                            int insertion_idx = closing_tag_idx - closing_tag.length();
                            // the tag in the document is opened so '/' needs to be inserted to close it
                            (*it2).second.insert(1, "/");
                            // The closing tag is just the opening tag after inserting '/' and removing attribute
                            string correct_closing = SString::stringToList((*it2).second)[0];
                            correct_closing = (correct_closing[correct_closing.length() - 1] == '>') ? correct_closing : correct_closing + '>';
                            // correct insertion index and update insertion offset array
                            update_ins_offset(ins_off_pair_list, insertion_idx, correct_closing.length());
                            // insert corrected tag at estimated position
                            validated_xml.insert(insertion_idx, correct_closing);
                            // add respective error message
                            detected_errors += "Missing Closing Tag\t" + (*it2).second + " at position: " + to_string(insertion_idx) + "\n";
                            // remove the opened tag that was jus close from linked list
                            opened_tags.erase(it2);
                            // assign the new iterator back to original node because it was just removed
                            it2 = it;
                        }
                    } while (closing_tag_idx > opening_tag_idx);
                    // finally remove both opened and closed tag that were matched from linke lists
                    closed_tags.pop_front();
                    opened_tags.erase(it);
                    // go to next closed tag and repeat
                    break;
                }

            }
            // go to next node in opening tags
            advance(it, 1);
            if (it == opened_tags.end()) {
                isFinishied = true;
                break;
            }
        }
    }
    // Stage 4 : clean extra tags
    // if there are both opening tags and closing tags remaining
    if (opened_tags.size() != 0 && closed_tags.size() != 0) {
        // insert missing opening tags after the last opened tag in the list
        int closed_tag_insert_idx = opened_tags.back().first;
        // insert missing closing tags after the last closed tag in the list
        int opened_tag_insert_idx = closed_tags.back().first;
        // loop over closed tags and add opening tags like in stage 3
        while (closed_tags.size() > 0) {
            int insertion_idx = closed_tag_insert_idx + 1;
            string correct_opening = closed_tags.front().second.erase(1, 1);
            update_ins_offset(ins_off_pair_list, insertion_idx, correct_opening.length());
            detected_errors += "Missing Opening Tag\t" + correct_opening + " at the begining" + "\n";
            validated_xml.insert(insertion_idx, correct_opening);
            closed_tags.pop_front();
        }
        // loop over opened tags and add closing tags like in stage 3
        while (opened_tags.size() > 0) {
            int insertion_idx = opened_tag_insert_idx + 1;
            string correct_closing = opened_tags.front().second.insert(1, "/");
            update_ins_offset(ins_off_pair_list, insertion_idx, correct_closing.length());
            detected_errors += "Missing Closing Tag\t" + correct_closing + " at the end" + "\n";
            validated_xml.insert(insertion_idx, correct_closing);
            opened_tags.pop_front();
        }
    }
    // if there are only opening tags remaining
    else if (opened_tags.size() != 0 && closed_tags.size() == 0) {
        // insert at the end of the string
        int opened_tag_insert_idx = xml.length();
        // loop over opened tags and add closing tags like in stage 3
        while (opened_tags.size() > 0) {
            int insertion_idx = opened_tag_insert_idx;
            string correct_closing = opened_tags.front().second.insert(1, "/");
            update_ins_offset(ins_off_pair_list, insertion_idx, correct_closing.length());
            detected_errors += "Missing Closing Tag\t" + correct_closing + " at the end" + "\n";
            validated_xml.insert(insertion_idx, correct_closing);
            opened_tags.pop_front();
        }
    }
    // if there are only closing tags remaining
    else if (opened_tags.size() == 0 && closed_tags.size() != 0) {
        // insert at the begining of the string
        int closed_tag_insert_idx = 0;
        // loop over closed tags and add opening tags like in stage 3
        while (closed_tags.size() > 0) {
            int insertion_idx = closed_tag_insert_idx;
            string correct_opening = closed_tags.front().second.erase(1, 1);
            update_ins_offset(ins_off_pair_list, insertion_idx, correct_opening.length());
            detected_errors += "Missing Opening Tag\t" + correct_opening + " at the begining" + "\n";
            validated_xml.insert(insertion_idx, correct_opening);
            closed_tags.pop_front();
        }
    }
    // update errors detected and current text with the validate xml and errors message
    errors_detected = (detected_errors.compare("") == 0) ? "No errors Detected\n" : detected_errors;
    current_text = validated_xml;
    update_attributes();
}




