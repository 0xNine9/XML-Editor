#pragma once
#include <string>
#include <vector>
using namespace std;

class User
{
public:
    //  attributes
    string name;
    int id;
    vector<int> followers;

    // methods
    User();
    void addFollower(int follower);
    static string find_user_name_by_id(int user_id, vector <User> users);
    static int find_user_by_name(string user_name, vector <User> users);
    static int find_user_by_id(int user_id, vector <User> users);
};