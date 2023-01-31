#include "formatter.h"

namespace std
{

    string minify(Node* node) {
        string minified_xml = "<" + node->TagName + ">";
        for (int i = 0; i < node->children.size(); i++) {
            minified_xml += minify(node->children[i]);
        }
        minified_xml += erase_unwanted_chars(node->TagValue) + "</" + node->TagName + ">";
        return minified_xml;
    }
    string prettify(Node* node, int level) {
        string prettified_xml = insert_taps(level) + "<" + node->TagName + ">";
        for (int i = 0; i < node->children.size(); i++) {
            prettified_xml += "\n";
            prettified_xml += prettify(node->children[i],level+1);
        }
        string tag_value = format_newLine(erase_unwanted_chars(node->TagValue), level);
        if(tag_value.length() >= 75) prettified_xml += "\n" + insert_taps(level) +  tag_value +"\n" + insert_taps(level) + "</" + node->TagName + ">";
        else if (node->children.size() > 0) prettified_xml += "\n" + insert_taps(level) + tag_value + "</" + node->TagName + ">";
        else prettified_xml +=  tag_value  + "</" + node->TagName + ">";
        //minified_xml += "\n";
        return prettified_xml;
    }
    string convert_json(Node* node, int level) {
        string json = "";
        if (node->children.size() > 1) json += "\n" + insert_taps(level) + "\"" + node->TagName + "\":[\n" + insert_taps(level) + "{";
        else if (node->children.size() == 1) json += "\n" + insert_taps(level) + "\"" + node->TagName + "\":{";
        else if (node->children.size() == 0)
            json += "\n" + insert_taps(level) + "\"" + node->TagName + "\":\"" + format_newLine(erase_unwanted_chars(node->TagValue), level) + "\"";
        for (int i = 0; i < node->children.size(); i++) {
            json += convert_json(node->children[i], level + 1);
        }
        if (node->children.size() > 0) json += "\n" + insert_taps(level) + "}";
        return json;
    }

    string validate(string xml) {
        list<pair<int,string>> opened_tags;
        list<pair<int, string>> closed_tags;
        vector<pair<int, string>> values;
        string validated_xml = xml;
        string value = "";
        string tag = "";
        // Initialising opened tags, closed tags and values
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
                tag = erase_unwanted_chars(tag,true);
                value = erase_unwanted_chars(value);
                // add index,name pair for every list correctly
                if (tag[1] != '/') opened_tags.push_back(make_pair(i, tag));
                else if (tag[1] == '/') {
                    closed_tags.push_back(make_pair(i, tag));
                }
                bool cond = value.compare("")!=0 && value.compare(" ") != 0;
                if(cond) values.push_back(make_pair(i - value.length(), value));
                value = "";
                tag = "";
            }
            else {
                value += xml[i];
            }
        }
        // error detection and correction
        // looping over closed tags
        while(closed_tags.size() >0){
            // if there are no more oepning tags exit
            if (opened_tags.size() == 0) break;
            // get closing tag index and tagName
            string closing_tag = closed_tags.front().second;
            int closing_tag_idx = closed_tags.front().first;
            cout << closing_tag_idx<<"\n";
            if (closing_tag_idx > 540) {
                cout << "\n";
            }
            // iterator for opened tags
            list<pair<int, string>>::iterator it = opened_tags.begin();
            // iterate on all opening tags
            while (opened_tags.size() > 0) {
                // get opening tag index and tagName
                int opening_tag_idx = (*it).first;
                string opening_tag = stringToList((*it).second)[0];
                opening_tag = (opening_tag[opening_tag.length() - 1] == '>') ? opening_tag : opening_tag + '>';
                // if opening tag equal closing tag
                if (opening_tag.compare(closing_tag.erase(1, 1))==0) {
                    cout << opening_tag << "\t" << closing_tag << "\n";
                    //check if opening came after closing
                    if (closing_tag_idx < opening_tag_idx) {
                        // opening tag is missing in this position add it!
                        cout << "Missing Opening Tag\t" << closing_tag << "\n";
                        // if the first tag is missing insert at the begining
                        int insertion_idx = 0;
                        // otherwise insert just before the closest value before closing tag
                        for (int i = 0; i < values.size(); i++) {
                            if (values[i].first < closing_tag_idx) insertion_idx = values[i].first;
                            else break;
                        }
                        // here the closing tag is actually the opening because the '/' was earsed in the if condition at line 90
                        string correct_oepning = closing_tag;
                        validated_xml.insert(insertion_idx, correct_oepning);
                        // remove first closed tag from linked list
                        closed_tags.pop_front();
                        // go to next closed tag and repeat
                        break;
                    }
                        // else check if there are any opening tags between opening and closing
                    else {
                        // if last tag is reached erase both closing and opening and exit the loop
                        if (opening_tag_idx == opened_tags.back().first) {
                            closed_tags.pop_front();
                            opened_tags.erase(it);
                            break;
                        }
                        // create new iterator to check next opening tags before or after current closing tag
                        list<pair<int, string>>::iterator it2 = it;
                        do {
                            advance(it2, 1);
                            opening_tag_idx = (*it2).first;
                            // if there are any tags it means it is opened but not closed
                            if (closing_tag_idx >= opening_tag_idx) {
                                cout << "Missing Closing Tag\t" << (*it2).second << "\n";
                                // closing tag is inserted just before the current closing tag
                                int insertion_idx = closing_tag_idx - closing_tag.length();
                                // the tag in the document is opened so '/' needs to be inserted to close it
                                (*it2).second.insert(1, "/");
                                string correct_closing = (*it2).second;
                                validated_xml.insert(insertion_idx, correct_closing);
                                // remove the opened tag that was jus close from linked list
                                opened_tags.erase(it2);
                                // assign the new iterator back to original node because it was just removed
                                it2 = it;
                            }
                        } while (closing_tag_idx > opening_tag_idx);
                        // finally remove both opened and closed tag that were matched from linke lists
                        closed_tags.pop_front();
                        opened_tags.erase(it);
                    }
                    // go to next closed tag and repeat
                    break;
                }
                // restore '/' to closing tag that was removed in fi condition at line 90
                closing_tag.insert(1, "/");
                // go to next node in opening tags
                advance(it, 1);
            }
        }
        return validated_xml;
    }
}




