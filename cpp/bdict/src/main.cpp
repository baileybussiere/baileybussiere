#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "command.h"

using namespace std;

vector<command> commands;
string pn = "[bdict] ";

vector<entry> entries;

int fib(int n);
void init();
bool do_input(string input);

int main()
{
	string input = "";
	bool exit = false;
	while (!exit)
	{
		cout << pn << "Please enter a command:" << endl;
		cin >> input;
		if (input == "exit")
		{
			exit = true;
			cout << "Would you like to save? (yod/nord) ";
			string s;
			cin >> s;
			if (s == "")
			{
				cout << "Cancelling..." << endl;
				exit = false;
			}
			else if (s == "yod" || s == "Yod")
				do_input("save");
			else if (s != "nord" && s != "Nord")
			{
				cout << "Cancelling..." << endl;
				exit = false;
			}
		}
		else if (!do_input(input))
			cout << pn << "Invalid command." << endl;
	}
	return 0;
}

bool do_input(string input)
{
	string pn = "[input_handler] ";
	int substr_start, substr_end = -1;
	int i = 0;
	vector<string> parsed_input;
	while (i < input.length())
	{
		if (input.at(i) == ' ')
		{
			if (substr_start > 0 && substr_end >= substr_start)
			{
				parsed_input.push_back(input.substr(substr_start, substr_end + 1));
				substr_start, substr_end = -1;
			}
		}
		else
		{
			if (substr_start == -1)
				substr_start = i;
			else
				substr_end = i;
		}
	}
	if (substr_start > 0 && substr_end >= substr_start)
		parsed_input.push_back(input.substr(substr_start, substr_end + 1));

	//Common-sense checks:
	if (parsed_input.size() == 0)
	{
		cout << pn << "Input is empty." << endl;
		return false;
	}
	else if (parsed_input.size() > 10)
	{
		cout << pn << "Too many words." << endl;
		return false;
	}

	//Send that 'ish of to command
	vector<command>::iterator command_index = find_if(commands.begin(), commands.end(), [=] (command c) -> bool {return c.text == parsed_input[0];});
	if (command_index == commands.end())
	{
		cout << pn << "Invalid command: " << parsed_input[0] << endl;
		return false;
	}
	else
		(*command_index).perform_command(parsed_input);
}

void init()
{
	//commands.push_back(command("make", 3, &command_make).set_desc("Makes a new dictionary entry under <arg2> with definition <arg1> and part of speech <arg0>."));
	//commands.push_back(command("delete", 1, &command_delete).set_desc("Searches for the indicated entry <arg0> and asks for permission before deleting it, if found."));
	//commands.push_back(command("save", 0, &command_save).set_desc("Saves the current dictionary to the bin/dict, appending '.old' to any already existing file with the same name."));
	commands.push_back(command("help", 0, &command_help).set_desc("Prints the help."));
}

bool command_help(vector<string> input)
{
	string pn = "[help] ";
	for (vector<command>::iterator comm_ind = commands.begin(); comm_ind < commands.end(); ++comm_ind)
	{
		cout << pn << (*comm_ind).text;
		for (int i = 0; i < (*comm_ind).num_args; ++i)
			cout << " <arg" << i << ">";
		cout << ": " << (*comm_ind).desc << endl;
	}
	return true;
}

bool command_make(vector <string> input)
{
	string pn = "[make] ";
	
}

int fib(int n)
{
	if (n <= 1)
		return n;
	else
		return fib(--n) + fib(--n);
}
