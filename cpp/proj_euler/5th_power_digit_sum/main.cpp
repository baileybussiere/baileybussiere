// This program searches for numbers whose digits' fifth powers sum to themselves.
// Bailey Bussiere

#include <iostream>

int pow(int, int);

int whereis(int, int*);

int main()
{
	// comb is an index representing a combination of digits.
	// The limit 354294 is derived from noting that the greatest n for which n*9^5 > 10^n is 6.
	// n*9^5 = 354264.
	for (int comb = 10; comb < 354264; comb++)
	{
		int num = 0;
		for (int j = 0; j < 6; j++)
		{
			if (comb < pow(10, j))
				j = 6;
			else
				num += pow((comb / pow(10, j)) % 10, 5);
		}
		if (num == comb)
			std::cout << num << std::endl;
	}
}

int pow(int base, int exponent)
{
	int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

int whereis(int element, int *array)
{
	for (int i = 0; i < 6; ++i)
	{
		if (element == array[i])
			return i;
	}
}

