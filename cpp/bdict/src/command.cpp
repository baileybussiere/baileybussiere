#include <string>
#include "command.h"

using namespace std;

command::command(string text, int num_args, action_func action)
{
	this->text = text;
	this->num_args = num_args;
	this->action = action;
}

bool command::perform_command(vector<string> input)
{
	if (action)
		(*action)(input);
}

command command::set_desc(string desc)
{
	this->desc = desc;
	return *this;
}
