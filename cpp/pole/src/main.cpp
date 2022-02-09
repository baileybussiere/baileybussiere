#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
using namespace std;

pair<int, long> v_vals[256]{};
long v_hashes[256]{};
int v_nextaddr{0};
pair<int, long> v_set(pair<int, long> arg1, pair<int, long> arg2);
long v_hash(string s);
pair<int, long> v_create(pair<int, long> arg);
void v_delete(pair<int, long> arg);

float f_vals[64]{};
int f_nextaddr{0};
pair<int, long> f_create(float f);

float f_pers_vals[64]{};
bool f_pers_slots[64]{false};
void f_set_nextaddr();
int f_pers_nextaddr{0};

//workaround
string func_vals[64]{};
int func_nextaddr{0};
pair<int, long> f_create(string s);
//

array<char, 90> alphabet = {'_', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a', 'b',
	'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
	's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', ';', ',', '\'', '.', '"', '?', '%', '^', '*', '!', '@',
	'#', '$', '-', '+', '=', '/', '\\', '<', '>', '|', '[', ']', '{', '}', '(', ')'};

array<string, 64> functions = {"+", "-", "*", "/", "\\",
	"<", ">", "%", "if.", "~if.",
	"=", "<-", "~", ":", ";",
	"+.", "-.", "*.", "/.", "\\.",
	"<.", ">.", "{.", "}.", "$",
	"!", "?", "#", "{", "}",
	"n.", "func.", "f.", "x.",
	"wh.", "~wh."};
array<unsigned int, 64> func_arities = {2, 2, 2, 2, 2,
	2, 2, 2, 3, 3,
	2, 2, 1, 2, 2,
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 1, 1, 1, 1,
	1, 2, 0, 0,
	2, 2};

float modulusif(int, float);
float modulusfi(float, int);
float modulusff(float, float);

long get_int(pair<int, long> p);
float get_float(pair<int, long> p);
string get_string(pair<int, long> p);

bool is_int(pair<int, long> p);
bool is_float(pair<int, long> p);
bool is_string(pair<int, long> p);

pair<int, long> (*func_lambdas[64])(vector<pair<int, long>>) = {[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, get_int(args[0]) + get_int(args[1]));
				else if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))) return f_create((is_int(args[0])? get_int(args[0]): get_float(args[0])) + (is_int(args[1])? get_int(args[1]): get_float(args[1])));
				else if(is_string(args[0]) && is_string(args[1])) return make_pair(2, 0);
				else{cout << error << "Invalid type or combination of types passed to '+'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, get_int(args[1]) - get_int(args[0]));
				else if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))) return f_create((is_int(args[1])? get_int(args[1]): get_float(args[1])) - (is_int(args[0])? get_int(args[0]): get_float(args[0])));
				else{cout << error << "Invalid type or combination of types passed to '-'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, get_int(args[0]) * get_int(args[1]));
				else if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))) return f_create((is_int(args[0])? get_int(args[0]): get_float(args[0])) * (is_int(args[1])? get_int(args[1]): get_float(args[1])));
				else{cout << error << "Invalid type or combination of types passed to '*'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, get_int(args[1]) / get_int(args[0]));
				else if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))) return f_create((is_int(args[1])? get_int(args[1]): get_float(args[1])) / (is_int(args[0])? get_int(args[0]): get_float(args[0])));
				else{cout << error << "Invalid type or combination of types passed to '/'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))){
				if(is_int(args[1])){
					if(is_int(args[0])) return make_pair(1, (get_int(args[0]) % get_int(args[1])) == 0? 1: 0);
					else return make_pair(1, modulusfi(get_float(args[0]), get_int(args[1])) == 0.0? 1: 0);
				}else{
					if(is_int(args[0])) return make_pair(1, modulusif(get_int(args[0]), get_float(args[1])) == 0.0? 1: 0);
					else return make_pair(1, modulusff(get_float(args[0]), get_float(args[1])) == 0.0? 1: 0);
				}}},
		[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, (get_int(args[1]) < get_int(args[0]))? 1: 0);
				else if(is_float(args[0]) && is_float(args[1])) return make_pair(1, (get_float(args[1]) < get_float(args[0]))? 1: 0);
				else{cout << error << "Invalid type or combination of types passed to '<'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, (get_int(args[1]) > get_int(args[0]))? 1: 0);
				else if(is_float(args[0]) && is_float(args[1])) return make_pair(1, (get_float(args[1]) > get_float(args[0]))? 1: 0);
				else{cout << error << "Invalid type or combination of types passed to '>'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {if((is_int(args[0]) || is_float(args[0])) && (is_int(args[1]) || is_float(args[1]))){
				if(is_int(args[1])){
					if(is_int(args[0])) return make_pair(1, get_int(args[1]) % get_int(args[0]));
					else return f_create(modulusif(get_int(args[1]), get_float(args[0])));
				}else{
					if(is_int(args[0])) return f_create(modulusfi(get_float(args[1]), get_int(args[0])));
					else return f_create(modulusff(get_float(args[1]), get_float(args[0])));
				}}else{cout << error << "Invalid type or combination of types passed to '%'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return get_int(args[0]) == 1? args[2]: args[1];
				else{cout << error << "Non-integer type passed as third argument of 'if.'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return get_int(args[0]) == 0? args[2]: args[1];
				else{cout << error << "Non-integer type passed as third argument of '~if.'" << endl; return make_pair(-1, 3);}},
		[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0]) && is_int(args[1])) return make_pair(1, (get_int(args[1]) == get_int(args[0]))? 1: 0);
				else if(is_float(args[0]) && is_float(args[1])) return make_pair(1, (get_float(args[1]) == get_float(args[0]))? 1: 0);
				else if(is_string(args[0]) && is_string(args[1])) return make_pair(1, (get_string(args[1]) == get_string(args[0]))? 1: 0);
				else{cout << error << "Invalid type or combination of types passed to '='" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {return v_set(args[0], args[1]);},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return (get_int(args[0]) == 0)? make_pair(1, (long) 1): (get_int(args[0]) == 1)? make_pair(1, (long) 0): args[0];
				else if(is_float(args[0])) return f_create((get_float(args[0]) == 0.0)? 1.0: (get_float(args[0]) == 1.0)? 0.0: get_float(args[0]));
				else{cout << error << "Invalid type or combination of types passed to '~'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
		[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return make_pair(1, get_int(args[0]) * 2);
				else if(is_float(args[0])) return f_create(get_float(args[0]) * 2);
				else{cout << error << "Invalid type or combination of types passed to '+.'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return f_create((float) get_int(args[0]) / 2.0);
				else if(is_float(args[0])) return f_create(get_float(args[0]) / 2.0);
				else{cout << error << "Invalid type or combination of types passed to '+.'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return make_pair(1, get_int(args[0]) * get_int(args[0]));
				else if(is_float(args[0])) return f_create(get_float(args[0]) * get_float(args[0]));
				else{cout << error << "Invalid type or combination of types passed to '*.'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {
				if(is_int(args[0])) return f_create(sqrt(get_int(args[0])));
				else if(is_float(args[0])) return f_create(sqrt(get_float(args[0])));
				else{cout << error << "Invalid type or combination of types passed to '/.'" << endl; return make_pair(-1, 3);}},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);}, //Prime check algorithm maybe?
		[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(1, args[0].second * 2);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(1, args[0].second / 2);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(1, args[0].second * args[0].second);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(1, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
		[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
		[](vector<pair<int, long>> args)->pair<int, long> {return v_create(args[0]);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);},
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);}
	[](vector<pair<int, long>> args)->pair<int, long> {
				if (is_int(args[0])) while (get_int(args[0]) == 1)? 
				return make_pair(0, 0);}
	[](vector<pair<int, long>> args)->pair<int, long> {return make_pair(0, 0);}
	};

string error = "[ERR] ";

int char_type(char c);
pair<int, long> process(string *tokens, int length);
bool val_var(string s);
bool val_num(string s);
bool val_string(string s);
pair<int, long> as_num(string s);
pair<int, long> as_string(string s);
string print(pair<int, long> p);
int arity(int id);
vector<string> tokenise(string s);

/*pass values as pair<int, long>, first val:
	-2 => unitialized variable,
	-1 => error,
	0 => initialized variable,
	1 => int,
	2 => string,
	3 => float,
	4 => function*/
//-2: second value is hash of variable's name
//-1: second value is error type: 0 => invalid argument, 1 => no primitive with that name, 2 => no var with that name
//0: second value is address in v_vals, hash list
//1: second value is value of int
//2: second value is index of string in s_vals
//3: second value is index of float in f_vals
//4: second value is index of binary tree in func_trees

string *current_index = 0;
string *final_index;

//===========//
//	     //
// DEBUGGING //
//	     //
//===========//
bool debug = false;

int main()
{
	bool exit{false};
	string input{"exit"};
	while (!exit)
	{
		cout << ":";
		getline(cin, input);
		if(input == "`exit")
			exit = true;
		else if(input == "`debugon")
			debug = true;
		else if(input == "`debugoff")
			debug = false;
		else
		{
			f_nextaddr = 0; //clear float mem
			vector<string> tokens = tokenise(input);
			/*for (string q: tokens)
				cout << q << " ";*/
			if(tokens.back() == "```Err")
				cout << "Parse Error" << endl;
			else
				cout << print(process(&tokens[0], tokens.size(), false)) << endl;
		}
	}
}

vector<string> tokenise(string s)
{
	vector<string> tokens{};
	bool commenting{false};
	bool quoting{false};
	int comm_end{0};
	bool err{false};
	int c_t{-1};
	int prev_ct{-1};
	string buffer{""};
	for(long i{s.length() - 1}; i >= 0; i--)
	{
		c_t = char_type(s.at(i));
		if(!quoting)
		{
			if(!commenting)
			{
				switch(c_t)
				{
					case -1:
						err = true;
						cout << error << "Character at " << i << " is invalid." << endl;
						break;
					case 0:
						if(buffer != "")
						{
							reverse(buffer.begin(), buffer.end());
							tokens.push_back(buffer);
							buffer = "";
						}
						break;
					case 3:
						commenting = true;
						comm_end = i;
						if (buffer != "")
						{
							reverse(buffer.begin(), buffer.end());
							tokens.push_back(buffer);
							buffer = "";
						}
						break;
					case 4:
						err = true;
						cout << error << "Unpaired '(' at " << i << ". To comment out the rest of a line use '|'." << endl;
						break;
					case 5:
						tokens.clear();
						buffer = "";
						break;
					case 6:
						if(buffer != "")
						{
							reverse(buffer.begin(), buffer.end());
							tokens.push_back(buffer);
							buffer = "";
						}
						buffer = "\"";
						quoting = true;
					default:
						buffer += s.at(i);
						break;
				}
			}
			else
				if(c_t == 4)
					commenting == false;
				else if(c_t == 5)
				{
					commenting == false;
					tokens.clear();
				}
			prev_ct = c_t;
		}
		else
		{
			buffer += s.at(i);
			if(c_t == 6)
			{
				reverse(buffer.begin(), buffer.end());
				tokens.push_back(buffer);
				quoting = false;
				buffer = "";
			}
		}
	}
	if(quoting)
	{
		cout << error << "Unpaired quote" << endl;
		tokens.push_back("```Err");
	}
	else if(buffer != "")
	{
		reverse(buffer.begin(), buffer.end());
		tokens.push_back(buffer);
	}
	if(err)
	{
		tokens.push_back("```Err");
	}
	return tokens;
}

int char_type(char c)
{
	if (c == ' ')
		return 0;
	else if(c == '"')
		return 6;
	else if (c == ')')
		return 3;
	else if (c == '(')
		return 4;
	else if (c == '|')
		return 5;
	for (char *i = alphabet.begin(); i < alphabet.end(); ++i)
	{
		if (c == *i)
		{
			if (i - alphabet.begin() < 63)
				return 1;
			else
				return 2;
		}
	}
	return -1;
}

int function_id(string s)
{
	if (debug) cout << "searching for function... ";
	for (string *i = functions.begin(); i < functions.end(); i++)
	{
		if((*i) == s)
		{
			if (debug) cout << i - functions.begin() << endl;
			return i - functions.begin();
		}
	}
	if (debug) cout << "not found." << endl;
}

pair<int, long> process(string *tokens, int length, bool defer)
{
	current_index = tokens + 1;
	if (debug) cout << "Processing..." << endl;
	if (val_var(*tokens))
	{
		long hash = v_hash(*tokens);
		auto addr = find(v_hashes, v_hashes + v_nextaddr, hash);
		pair<int, long> ret{};
		if (addr == v_hashes + v_nextaddr)
			ret = make_pair(-2, hash);
		else
			ret = make_pair(0, addr - v_hashes);
		if (debug) cout << "(" << ret.first << ", " << ret.second << ")" << endl;
		return ret;
	}
	else if (val_num(*tokens))
	{
		pair<int, long> ret = as_num(*tokens);
		if(debug) cout << "(" << ret.first << ", " << ret.second << ")" << endl;
		return ret;
	}
	else if (val_string(*tokens))
	{
		pair<int, long> ret = as_string(*tokens);
		if(debug) cout << "(" << ret.first << ", " << ret.second << ")" << endl;
		return ret;
	}
	else
	{
		int f_depth = f_nextaddr;
		int funcid = function_id(*tokens);
		if(funcid != -1)
		{
			if(length - (current_index - tokens) >= arity(funcid))
			{
				if(needs_deferred_processing(funcid))
				{
					
				}
				else
				{
					vector<pair<int, long>> args{};
					for(int i = 1; i <= arity(funcid); i++)
					{
						pair<int, long> p = process(current_index, length - (current_index - tokens));
						if(p.first == -1)
						{
							f_nextaddr = f_depth;
							return p;
						}
						else if(p.first == -2 && funcid != 30) //uninitialized var as arg to anything but 'n.' (id: 30)
						{
							cout << error << "No variable with that name" << endl;
							f_nextaddr = f_depth;
							return make_pair(-1, 2);
						}
						else
						{
							args.push_back(p);
						}
					}
					pair<int, long> ret_val = func_lambdas[funcid](args);
					if(debug)
						cout << "(" << ret_val.first << ", " << ret_val.second << ")" << endl;
					if(is_float(ret_val)) //clear used float mem
					{
						f_nextaddr = f_depth + 1;
						f_vals[f_depth] = f_vals[ret_val.second];
						ret_val.second = f_depth;
					}
					else if(is_string(ret_val)) //clear used string mem
					{
					}
					return ret_val;
				}
			}
			else
			{
				cout << error << "Too few arguments passed to " << functions[funcid] << endl;
				f_nextaddr = f_depth;
				return make_pair(-1, 0);
			}
		}
		else
			return make_pair(-1, 1);
	}
}

int arity(int id)
{
	return func_arities[id];
}

bool needs_deffered_processing(int id)
{
	return (id == 8 || id == 9 || id == 34 || id == 35)
}

pair<int, long> as_num(string s)
{
	if(s.find(".") != s.npos)
	{
		return f_create(stof(s));
	}
	else
		return make_pair(1, stoi(s));
}

pair<int, long> as_string(string s)
{
	
}

bool val_num(string s)
{
	for(unsigned int i{0}; i < s.length(); i++)
	{
		if(!isdigit(s.at(i)))
		{
			if(!(s.at(i) == '.' && i != s.length() - 1) && !(s.at(i) == '-' && i == 0 && s.length() > 1))
				return false;
		}
	}
	return true;
}

bool val_var(string s)
{
	if (isdigit(s.at(0)))
		return false;
	else if(s.at(s.length() - 1) != '.')
	{
		for (char &i : s)
		{
			for (char *j = alphabet.begin(); j < alphabet.end(); j++)
			{
				if (i == *j)
				{
					if (j - alphabet.begin() > 62)
						return false;
				}
			}
		}
		return true;
	}
	else return false;
}

bool val_string(string s)
{
	if(s.at(0) == '"' && s.at(s.length() - 1) == '"')
		return true;
	else return false;
}

string print(pair<int, long> p)
{
	if(is_int(p))
		return to_string(get_int(p));
	else if(is_float(p))
		return to_string(get_float(p));
	else if(is_string(p))
		return get_string(p);
	else if(p.first == 0 && v_vals[p.second].first == 0)
		return "unitialized.";
	else if(p.first == -2)
		return "No variable with that name";
	else
		return "";
}

//Mem allocation
pair<int, long> f_create(float f)
{
	f_vals[f_nextaddr] = f;
	pair<int, long> p = make_pair(3, f_nextaddr);
	f_nextaddr++;
	return p;
}

void f_set_nextaddr()
{
	for(int i{0}; i < 64; i++)
	{
		if(!f_pers_slots[i])
		{
			f_pers_nextaddr = i;
			return;
		}
	}
	cout << error << "Out of float memory" << endl;
	return;
}

pair<int, long> v_create(pair<int, long> arg)
{
	if(arg.first == -2)
	{
		v_hashes[v_nextaddr] = arg.second;
		v_vals[v_nextaddr] = make_pair(0, 0);
		v_nextaddr++;
		return make_pair(0, v_nextaddr - 1);
	}
	else
	{
		cout << error << "Invalid argument to 'n.'" << endl;
		return make_pair(-1, 0);
	}
}

void v_delete(pair<int, long> arg)
{
	if(is_float(arg))
	{
		unsigned int slot = v_vals[arg.second].second;
		f_pers_slots[slot] = false;
		if(slot < f_pers_nextaddr)
			f_pers_nextaddr = slot;
		v_vals[arg.second] = make_pair(0, 0);
	}
	else if(is_string(arg))
	{
		//TODO
	}
}

pair<int, long> v_set(pair<int, long> arg1, pair<int, long> arg2)
{
	if(arg1.first == -2 || arg2.first == -2)
	{
		cout << error << "No variable with that name" << endl;
		return make_pair(-1, 2);
	}
	else if(arg1.first == -1)
		return arg1;
	else if(arg2.first == -1)
		return arg2;
	else if(arg1.first != 0)
	{
		cout << error << "Cannot set unmutable value" << endl;
		return make_pair(-1, 3);
	}
	else if(arg2.first == 0)
	{
		pair<int, long> val = v_vals[arg2.second];
		if(arg1.first != val.first)
			v_delete(arg1);
		switch(val.first)
		{
			case 0:
				cout << error << "Unitialized variable cannot be used to set value" << endl;
				return make_pair(-1, 3);
			case 2: //TODO
				return make_pair(0, 0);
			case 3:
				f_pers_vals[f_pers_nextaddr] = f_pers_vals[val.second];
				f_pers_slots[f_pers_nextaddr] = true;
				v_vals[arg1.second] = make_pair(3, f_pers_nextaddr);
				f_set_nextaddr();
				return arg1;
			default:
				v_vals[arg1.second] = val;
				return arg1;
		}
	}
	else
	{
		if(arg1.first != arg2.first)
			v_delete(arg1);
		switch(arg2.first)
		{
			case 2: //TODO
				return make_pair(0, 0);
			case 3:
				if(arg1.first != 3)
					v_delete(arg1);
				f_pers_vals[f_pers_nextaddr] = f_vals[arg2.second];
				f_pers_slots[f_pers_nextaddr] = true;
				v_vals[arg1.second] = make_pair(3, f_pers_nextaddr);
				f_set_nextaddr();
				return arg1;
			default:
				v_vals[arg1.second] = arg2;
				return arg1;
		}
	}
}

//Type Checking and Type Stuff
bool is_int(pair<int, long> p){return p.first == 1 || (p.first == 0 && v_vals[p.second].first == 1);}
bool is_float(pair<int, long> p){return p.first == 3 || (p.first == 0 && v_vals[p.second].first == 3);}
bool is_string(pair<int, long> p){return p.first == 2 || (p.first == 0 && v_vals[p.second].first == 2);}
bool is_function(pair<int, long> p){return p.first == 4 || (p.first == 0 && v_vals[p.second].first == 4);}
	/*NOTE: not type safe, use is_type() before using*/
long get_int(pair<int, long> p){return p.first == 0? v_vals[p.second].second: p.second;}
float get_float(pair<int, long> p){return p.first == 0? f_pers_vals[v_vals[p.second].second]: f_vals[p.second];}
string get_string(pair<int, long> p){return "";} //TODO

//Maffffff

float modulusif(int x, float y)
{
	int z = floor(x / y);
	return (float) x - y * z;
}
float modulusfi(float x, int y)
{
	int z = floor(x / y);
	return x - (float) y * z;
}
float modulusff(float x, float y)
{
	int z = floor(x / y);
	return x - y * z;
}
long v_hash(string s)
{
	int ret{0};
	for(unsigned int i{0}; i < s.length(); i++)
	{
		ret += s.at(i) << i;
	}
	return ret;
}

