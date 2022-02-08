#include <iostream>
#include <string>
#include <locale>
using namespace std;

int board_size{19};
string plr_b{"black"};
string plr_w{"white"};
char pass_w{0};
char pass_b{0};

bool place_piece(bool black)
{
	string input;
	bool good = false;
	while (cin >> input && !good)
	{
		if (isalpha(input.at(0)) && isdigit(input.at(1)) && (input.length == 2 || isdigit(input.at(2))))
		{
			if (
		}
	}
}

void move(bool black, char[][] board)
{
	string input;
	cout << "----NEW TURN----" << endl << "It is ";
	switch(black)
	{
		case true: cout << plr_b;
		case false: cout << plr_w;
	}
	cout << "'s turn." << endl;
	cout << "What would you like to do?" << endl << "1. pass, 2. play (default)" << endl << "Enter a number, or just enter nothing for the default move: ";
	cin >> input;
	if(input == "1")
	{
		cout << "Passing..." << endl;
		switch(black)
		{
			case true:
				pass_b = true;
				break;
			case false:
				pass_w = true;
				break;
		}
	}
	else
	{
		cout << "What position?" << endl << "Enter a position by listing a letter followed by a number with no spaces.";
		while (!place_piece(black))
			cout << "Input not understood. Here are some examples: 'a2', 'B12', 'm18'." << endl;
	}
	return;
}

bool check_end()
{
	return false;
}

int setup()
{
	return;
}

void territory(char** board)
{
	m
}

int main()
{
	setup();
	char board[board_size][board_size];
	bool go=true;
	while(go)
	{
		move(true, board);
		move(false, board);
		go = check_end();
	}
}

