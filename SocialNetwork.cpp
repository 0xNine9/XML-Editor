#include "SocialNetwork.h"
using namespace std;


// add each user's follower to its followers vector.
void SocialNetwork::followers_list(Node* root) {
    for (int i = 0; i < root->children.size(); i++) {
        User user;
        Node* user_node = root->children[i];
        if (user_node == NULL) throw invalid_argument("Not a valid Social network tree");
        int grand_childern_size = user_node->children.size();
		// iterate over user's children.
        for (int j = 0; j < grand_childern_size; j++) {
            Node* user_atr = user_node->children[j];
            if (user_atr == NULL) throw invalid_argument("Not a valid Social network tree");
			// if user's child TagName is id
            if (user_atr->TagName == "id") {
                user.id = stoi(user_atr->TagValue);
            }
			// if user's child TagName is name
            else if (user_atr->TagName == "name") {
                user.name = (user_atr->TagValue);
            }
			// if user's child TagName is followers
            else if (user_atr->TagName == "followers") {
                for (int z = 0; z < user_atr->children.size(); z++) {
                    Node* follower = user_atr->children[z];
                    if (follower == NULL) throw invalid_argument("Not a valid Social network tree");
                    Node* follower_id = follower->children[0];
                    if (follower_id == NULL) throw invalid_argument("Not a valid Social network tree");
                    user.addFollower(stoi(follower_id->TagValue));
                }
            }
        }
        users.push_back(user);
    }
}


// push posts into posts vector.
void SocialNetwork::posts_vector(Node* root) {
	// iterate over users
    for (int i = 0; i < root->children.size(); i++) {
        Node* user = root->children[i];
        if (user == NULL) throw invalid_argument("Not a valid Social network tree");
		// iterate over user's children
        for (int j = 0; j < user->children.size(); j++) {
            Node* user_tag = user->children[j];
            if (user_tag == NULL) throw invalid_argument("Not a valid Social network tree");
            if (user_tag->TagName == "posts") {
				// iterate over posts children
                for (int z = 0; z < user_tag->children.size(); z++) {
                    Node* post_node = user_tag->children[z];
                    if (post_node == NULL) throw invalid_argument("Not a valid Social network tree");
                    if (post_node->TagName == "post") {
						// push post node into posts vector.
                        posts.push_back(user_tag->children[z]);
                    }
                }
            }
        }
    }
}


// extracts post's body from posts vector using its location inside vector.
string SocialNetwork::get_post(int i) {
    for (int j = 0; j < posts[i]->children.size(); j++) {
        Node* post_node = posts[i]->children[j];
        if (post_node == NULL) throw invalid_argument("Not a valid Social network tree");
        if (posts[i]->children[j]->TagName == "body") {
			// return post's body
            return posts[i]->children[j]->TagValue;
        }
    }
}


// returns most influential user.
string SocialNetwork::most_influencer() {
	int size = 0;
	int most_influencer = 0;
	int i = users.size() - 1;
	// iterate over users vector.
	while (i >= 0) {
		if (users[i].followers.size() > size) {
			size = users[i].followers.size();
			most_influencer = i;
		}
		i--;
	}
	return "Most influencial user is: " + users[most_influencer].name +  "\n";
}


// returns most active user.
string SocialNetwork::most_active() {
	Dict<int> users_activity;
	// first one is is user id second one is activity
	for (int i = 0; i < users.size(); i++) {
		users_activity.append(to_string(users[i].id), 0);
	}
	int size = users.size() - 1;
	// iterate over users vector.
	while (size >= 0) {
		User user = users[size];
		int followers_size = users[size].followers.size() - 1;
		// iterate over user's followers.
		while (followers_size >= 0) {
			string id = to_string(user.followers[followers_size]);
			// check if users_activity contains follower's id.
			bool is_user = users_activity.contain(id);
			if (is_user) {
				// increment value bound to the follower's id.
				int user_activity = users_activity.get(id);
				users_activity.set(id, user_activity + 1);
			}
			followers_size--;
		}
		size--;
	}
	// sort users_activity.
	users_activity.sort();
	cout << "\n";
	return "Most Active user is: " + User::find_user_name_by_id(stoi(users_activity.getKeys()[0]), users) + "\n";
}


SocialNetwork::SocialNetwork() {
}

// Social Network Constructor.
SocialNetwork::SocialNetwork(Node* tree) {
    followers_list(tree);
    posts_vector(tree);
    if(users.size() ==0) throw invalid_argument("Not a valid Social network tree");
    most_influencer_user = most_influencer();
    most_active_user = most_active();
}


// return most_influencer_user.
string SocialNetwork::getMostInfluencerUser(){ return most_influencer_user; }

// return most_active_user.
string SocialNetwork::getMostActiveUser() { return most_active_user; }

// return mutual followers between two users by users' names.
string SocialNetwork::mutual_followers(string user_1_name, string user_2_name) {
	string output = "";
	// get first user's location inside users vector.
	int user_1_loc = User::find_user_by_name(user_1_name, users);
	// get second user's location inside users vector.
	int user_2_loc = User::find_user_by_name(user_2_name, users);
	// check if user_1 and user_2 exist.
	if (user_1_loc != -1 && user_2_loc != -1) {
		// iterate over user_1 followers.
		for (int i = 0; i < users[user_1_loc].followers.size(); i++) {
			// iterate over user_2 followers.
			for (int j = 0; j < users[user_2_loc].followers.size(); j++) {
				if (users[user_1_loc].followers[i] == users[user_2_loc].followers[j]) {
					// append mutual followers to output string.
					output += "id:\t" + to_string(users[user_1_loc].followers[i]) + "\nName:\t" + User::find_user_name_by_id(users[user_1_loc].followers[i], users) + "\n";
				}
			}
		}
		return output;
	}
	return "User names not found in social network\n";
}


// return mutual followers between two users by users' ids.
string SocialNetwork::mutual_followers(int user_1_id, int user_2_id) {
    string output = "";
	// get first user's location inside users vector.
    int user_1_loc = User::find_user_by_id(user_1_id, users);
	// get second user's location inside users vector.
    int user_2_loc = User::find_user_by_id(user_2_id, users);
	// check if user_1 and user_2 exist.
    if (user_1_loc != -1 && user_2_loc != -1) {
		// iterate over user_1 followers.
        for (int i = 0; i < users[user_1_loc].followers.size(); i++) {
			// iterate over user_2 followers.
            for (int j = 0; j < users[user_2_loc].followers.size(); j++) {
                if (users[user_1_loc].followers[i] == users[user_2_loc].followers[j]) {
					// append mutual followers to output string.
                    output += "id:\t" + to_string(users[user_1_loc].followers[i]) + "\nName:\t" + User::find_user_name_by_id(users[user_1_loc].followers[i], users) + "\n";
                }
            }
        }
        return output;
    }
    return "User IDs not found in social network\n";
}


// return suggested followers for specific user name.
string SocialNetwork::suggested_followers(string user_name) {
	// get user's location inside users vector.
	int user_loc = User::find_user_by_name(user_name, users);
	// check if user exists.
	if (user_loc != -1) {
		vector<int> follower_suggessions_ids;
		string suggessions = "";
		int user_loc = User::find_user_by_name(user_name, users);
		int user_id = users[user_loc].id;
		// iterate over user's followers.
		for (int i = 0; i < users[user_loc].followers.size(); i++) {
			int follower_loc = User::find_user_by_id(users[user_loc].followers[i], users);
			// iterate over follower's followers.
			for (int j = 0; j < users[follower_loc].followers.size(); j++) {
				int id = users[follower_loc].followers[j];
				// 1) check if id isn't the same as the user himself 
				if (id != user_id) {
					bool isDuplicate = false;
					// 2) check if id isn't already in his followers list
					for (int dup_id : users[user_loc].followers) {
						if (id == dup_id) {
							isDuplicate = true;
							break;
						}
					}
					// 3) check if id isn't already suggested before
					if (!isDuplicate) {
						for (int dup_id : follower_suggessions_ids) {
							if (id == dup_id) {
								isDuplicate = true;
								break;
							}
						}
					}
					if (!isDuplicate) follower_suggessions_ids.push_back(id);
				}
			}
		}
		for (int id : follower_suggessions_ids) suggessions += "id:\t" + to_string(id) + "\nName:\t" + User::find_user_name_by_id(id, users) + "\n";
		return suggessions;
	}
	else {
		return "User doesn't exist";
	}
}


// return suggested followers for specific user id.
string SocialNetwork::suggested_followers(int user_id) {
	// get user's location inside users vector.
	int user_loc = User::find_user_by_id(user_id, users);
	// check if user exists.
	if (user_loc != -1) {
		vector<int> follower_suggessions_ids;
		string suggessions = "";
		// iterate over user's followers.
		for (int i = 0; i < users[user_loc].followers.size(); i++) {
			int follower_loc = User::find_user_by_id(users[user_loc].followers[i], users);
			// iterate over follower's follower.
			for (int j = 0; j < users[follower_loc].followers.size(); j++) {
				int id = users[follower_loc].followers[j];
				// 1) check if id isn't the same as the user himself 
				if (id != user_id) {
					bool isDuplicate = false;
					// 2) check if id isn't already in his followers list
					for (int dup_id : users[user_loc].followers) {
						if (id == dup_id) {
							isDuplicate = true;
							break;
						}
					}
					// 3) check if id isn't already suggested before
					if (!isDuplicate) {
						for (int dup_id : follower_suggessions_ids) {
							if (id == dup_id) {
								isDuplicate = true;
								break;
							}
						}
					}
					if (!isDuplicate) follower_suggessions_ids.push_back(id);
				}
			}
		}
		for (int id : follower_suggessions_ids) suggessions += "id:\t" + to_string(id) + "\nName:\t" + User::find_user_name_by_id(id, users) + "\n";
		return suggessions;
	}
	else {
		return "User doesn't exist";
	}
}


// search for post by topic or word inside post's body.
string SocialNetwork::search_posts(string key) {
	string posts_bodies = "";
	int counter = 1;
	// iterate over each post node.
	for (int i = 0; i < posts.size(); i++) {
		// iterate over post children.
		for (int j = 0; j < posts[i]->children.size(); j++) {
			if (posts[i]->children[j]->TagName == "topics") {
				// iterate over topics.
				for (int z = 0; z < posts[i]->children[j]->children.size(); z++) {
					// check if topic contains key.
					if (posts[i]->children[j]->children[z]->TagValue.find(key) != string::npos) {
						posts_bodies += "post number:\t" + to_string(counter++) + get_post(i) + "\n";
					}
				}
			}
			else if (posts[i]->children[j]->TagName == "body") {
				// check if body contains key.
				if (posts[i]->children[j]->TagValue.find(key) != string::npos) {
					posts_bodies += "post number:\t" + to_string(counter++) + posts[i]->children[j]->TagValue + "\n";
				}
			}
		}
	}
	return posts_bodies;
}
