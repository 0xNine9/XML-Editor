#pragma once
#include "User.h"
#include "tree.h"
#include "Dict.h"
#include <string>
#include <vector>
#include <stdexcept>

namespace std {
	class SocialNetwork
	{
	private:
		vector <Node*> posts;
		string most_influencer_user;
		string most_active_user;
		string most_influencer();
		string most_active();
		void followers_list(Node* root);
		void posts_vector(Node* root);
		string get_post(int i);
	public:
        SocialNetwork();
        SocialNetwork(Node* tree);
		vector<User> users;
		string getMostInfluencerUser();
		string getMostActiveUser();
		string mutual_followers(string user_1, string user_2);
		string mutual_followers(int user_1_loc, int user_2_loc);
		string suggested_followers(string user_name);
		string suggested_followers(int user_id);
		string search_posts(string key);
	};
}

