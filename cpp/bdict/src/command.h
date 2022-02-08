#include <vector>
#include <string>

#ifndef COMMAND_H
#define COMMAND_H

using namespace std;

class command
{
public:
	typedef bool (*action_func)(vector<string> input);
	command(string text, int num_args, action_func action);
	string text;
	int num_args;
	action_func action;
	string desc;

	bool perform_command(vector<string> input);
	command set_desc(string);
};

bool command_help(vector<string> input);
bool command_make(vector<string> input);
bool command_delete(vector<string> input);
bool command_save(vector<string> input);
#endif
