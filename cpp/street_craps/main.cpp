


#include <iostream>
#include <string>
#include <random>
using namespace std;

bool is_number(string s);

int money[];

int main()
{
	string input = "a";
	while (!is_number(input))
	{
		cout << "Enter number of players:" << endl;
		cin >> input;
	}
	int humans = stoi(input);
	input = "a";
	while (!is_number(input))
	{
		cout << "Enter number of bots:" << endl;
		cin >> input;
	}
	int bots = stoi(input);
	input = "a";
	while (!is_number(input))
	{
		cout << "Enter starting money for all players:" << endl;
		cin >> input;
	}
	money = int[bots + humans];
	fill(money, money + bots + humans, stoi(input));
	bool gameover = false;
	while (!gameover)
	{
		for (int i = 0; i < humans; i++)
		{
			
		}
	}
}

bool is_number(string s)
{
	return s.find_first_not_of("0123456789") == string::npos;
}
