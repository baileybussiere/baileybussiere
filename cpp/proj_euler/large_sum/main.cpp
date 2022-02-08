#include <iostream>
#include <string>

unsigned long to_ul(std::string);

int main()
{
	unsigned long sum = 0;
	for (int i = 0; i < 100; i++)
	{
		std::string input;
		std::cin >> input;
		input = input.substr(0, 11);
		sum += to_ul(input);
	}
	std::cout << sum << std::endl;
}

unsigned long to_ul(std::string s)
{
	unsigned long output = 0;
	for (int i = 0; i < s.length(); i++)
	{
		output *= 10;
		output += s.at(i) - '0';
	}
	return output;
}
