#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

using std::string;
using std::cout;
using std::cin;
using std::pow;
using std::vector;

char alphabet[]{'b', 'p', 'v', 'f', 'm', 'M', 'w', 'W', 'B', 'P', 'D', 'T', 'd', 't', 'z', 's', 'n', 'N', 'y', 'Y', 'l', 'L', 'Z', 'S', 'r', 'R', 'g', 'k', 'G', 'x', 'q', 'Q'};
char vowels[]{'a', 'A', 'O', 'e', 'o', 'E', 'U', 'I', 'u', 'i'};

bool is_vowel(char c)
{
	for(unsigned int i{0}; i < 10; ++i)
	{
		if(c == vowels[i]) return true;
	}
	return false;
}

unsigned int c_rank(char c)
{
	for(unsigned int i{0}; i < 34; ++i)
	{
		if(c == alphabet[i]) return i + 1;
	}
	return 33;
}

unsigned int v_rank(char c)
{
	for(unsigned int i{0}; i < 10; ++i)
        {
                if(c == vowels[i]) return i;
        }
        return 10;
}

double rank(string s)
{
	long double r{0};
	bool done{false};
	unsigned int start{0};
	for(unsigned int j{0}; !done; ++j)
	{
		unsigned char t{0};
		char v{0};
		bool g{false};
		unsigned int n{7};
		unsigned long int r1{0};
		for(unsigned int i{start}; i < std::min(7 + start, (unsigned int) s.size()); ++i)
		{
			char c = s.at(i);
			if(!is_vowel(c))
			{
				if(c == '\'')
					g = true;
				else if(c == '.')
				{
					start = i + 1;
					i = 7 + start;
				}
				else if(c == '-' || i == s.size() - 1)
				{
					i = 7 + start;
					done = true;
				}
				else if(c == '1')
					t = 1;
				else if(c == '2')
					t = 2;
				else
				{
					if(n > i)
						r1 += 60 * pow(33, 4 + start - i) * c_rank(c);
					else
						r1 += 60 * pow(33, 3 + n - i) * c_rank(c);
				}
			}
			else
			{
				v = c;
				n = i;
			}
		}
		r1 += 20 * t;
		r1 += 10 * g;
		r1 += v_rank(v);
		r += r1 / pow(71155260, j);
	}
	return r;
}

int main()
{
	vector<string> dic;
	string s{""};
	while(std::getline(cin, s))
		dic.push_back(s);
	std::sort(dic.begin(), dic.end(), [](string s1, string s2) {return rank(s1) < rank(s2);});
	for(unsigned int i{0}; i < dic.size(); ++i)
		cout << dic[i] << std::endl;
	return 0;
}
