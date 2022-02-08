#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

string greeting = "Welcome to Bill.com.\nEnjoy your stay.\n\n";
string username_prompt = "Please enter your username:\n";
string passwd_prompt = "Please enter your password:\n";
string new_username_prompt = "Please enter a username:\n";
string username_unavailable_mesg = "That username is already taken.\n";
string new_passwd_prompt = "Please enter a password:\n";
string verfy_passwd_prompt = "Please reenter the password:\n";
string name_prompt = "Enter a nickname we can refer to you as:\n";
string no_username_found_mesg = "No user found with that username.\n";
string incorr_passwd_mesg = "Incorrect password.\n";

class user
{
private:
	string passwd_encr;
public:
	user(string username, string passwd_encr);
	string username;
	string name;
	bool verify_login(string passwd);
	user set_name(string name);
};

string encrypt(string input);

vector<user> curr_users;

user::user(string username, string passwd_encr)
{
	this->passwd_encr = passwd_encr;
	this->username = username;
}

user user::set_name(string name)
{
	this->name = name;
	return *this;
}

bool user::verify_login(string passwd)
{
	return this->passwd_encr == encrypt(passwd);
}

vector<user>::iterator search_users(string username)
{
	return find_if(curr_users.begin(), curr_users.end(), [&] (user x){return x.username == username;});
}

void greet_new(user u)
{
	cout << "Welcome, " << u.name << "." << endl;
	cout << "Thank you for creating an account." << endl;
	return;
}

void greet(user u)
{
	cout << "Welcome back, " << u.name << "." << endl;
	cout << "We've missed you." << endl;
	return;
}

void suck_cock_of(user u)
{
	return;
}

void init();

user regstr();

user login();

int main()
{
	bool loggin = false;
	auto login_lambda = [&] ()->bool
		{
			string s;
			cin >> s;
			if(s == "l" || s == "L")
				loggin = true;
			else if (s == "r" || s == "R")
				loggin = false;
			else
			{
				cout << "Input not understood.\n";
				return true;
			}
			return false;
		};
	init();
	cout << greeting;
	user curr_user("", "");
	do
	{
		cout << "Type 'l' to log in, 'r' to register." << endl;
	}
	while (login_lambda());
	if (loggin)
	{
		curr_user = login();
		greet(curr_user);
	}
	else
	{
		curr_user = regstr();
		curr_users.push_back(curr_user);
		greet_new(curr_user);
	}
	suck_cock_of(curr_user);
}

user regstr()
{
	string username;
	string passwd;
	string passwd_verfy;
	auto usern_lambda = [=] ()->bool
		{
			if (search_users(username) != curr_users.end())
			{
				cout << username_unavailable_mesg;
				return true;
			}
			else return false;
		};
	auto passwd_lambda = [=] ()->bool
		{
			if (passwd != passwd_verfy)
			{
				cout << "Passwords given do not match." << endl;
				return true;
			}
			else return false;
		};
	do
	{
		cout << new_username_prompt;
		cin >> username;
	}
	while (usern_lambda());
	do
	{
		cout << new_passwd_prompt;
		cin >> passwd;
		cout << verfy_passwd_prompt;
		cin >> passwd_verfy;
	}
	while (passwd_lambda());
	string name;
	cout << name_prompt;
	cin >> name;
	return user(username, encrypt(passwd)).set_name(name);
}

user login()
{
	vector<user>::iterator user_ptr;
	string username;
	string passwd;
	auto lambda = [=]
		{
			vector<user>::iterator usr_ptr = search_users(username);
			if (user_ptr != curr_users.end())
			{
				if ((*user_ptr).verify_login(passwd))
					return false;
				else
				{
					cout << incorr_passwd_mesg;
					return true;
				}
			}
			else
			{
				cout << no_username_found_mesg;
				return true;
			}
		};
	do
	{
		cout << username_prompt;
		cin >> username;
		cout << passwd_prompt;
		cin >> passwd;

	}
	while (lambda());
	return *user_ptr;
}

vector<string> tokenize(string s)
{
	vector<string> svec;
	string buffer;
	for (int i = 0; i < s.length(); ++i)
	{
		if (i == s.length())
		{
			if (buffer != "")
				svec.push_back(buffer);
		}
		else if (s.at(i) == ' ' && buffer != "")
			svec.push_back(buffer);
		else
			buffer = buffer + s.at(i);
	}
	return svec;
}

void init()
{
	ifstream users_file("bin/users");
	string curr_line;
	while (getline(users_file, curr_line))
	{
		vector<string> args = tokenize(curr_line);
		curr_users.push_back(user(args[0], args[1]).set_name(args[2]));
	}
}

string encrypt(string s)
{
	return s;
}
