#include <iostream>
#include <fstream>

int initials_length{28};
std::string initials[]{"b", "p", "v", "f", "bv", "pf",
		"bh", "ph", "dh", "th", "bhdh", "phth",
		"d", "t", "z", "s", "dz", "ts",
		"zh", "sh", "dzh", "tsh",
		"g", "k", "gh", "x", "ggh", "kx"};

int main()
{
	std::ofstream file;
	file.open("verbs.txt");
	for(int i{0}; i < initials_length; ++i)
	{
		for(int j{0}; j < 3; ++j)
		{
			file << initials[i];
			file << "a";
			if(j > 0)
				file << j;
			file << "\n";
			file << initials[i];
			file << "ah";
			if(j > 0)
				file << j;
			file << "\n";
		}
	}
	file.close();
	return 0;
}
