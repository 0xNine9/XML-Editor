#include "User.h"
using namespace std;
User::User():name("NULL"), id(0){}
void User::addFollower(int follower)
{
    followers.push_back(follower);
}


// returns user's name corresponding to user's id.
string User::find_user_name_by_id(int user_id, vector <User> users) {
	// iterate over users
	for (int i = 0; i < users.size(); i++) {
		if (users[i].id == user_id) {
			return users[i].name;
		}
	}
	return "Can't find user";
}


// returns user's location inside user's vector corresponding to its name
int User::find_user_by_name(string user_name, vector <User> users) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].name == user_name) {
			return i;
		}
	}
	return -1;
}


// returns user's location inside user's vector corresponding to its id.
int User::find_user_by_id(int user_id, vector <User> users) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].id == user_id) {
			return i;
		}
	}
	return -1;
}