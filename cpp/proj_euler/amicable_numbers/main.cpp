#include <iostream>

unsigned square(int i) {return i*i;}

unsigned power(int n, int m)
{
	unsigned output = 1;
	for (int i = 0; i < m; i++)
	{
		output *= n;
	}
	return output;
}

void get_primes_bel(const unsigned, unsigned[], unsigned&);

unsigned get_factors(const unsigned, unsigned[]);

unsigned *primes;
unsigned num_primes;

int main()
{
	unsigned i;
	std::cin >> i;
	unsigned array[i];
	unsigned size;
	get_primes_bel(i / 2, array, size);
	primes = new unsigned[size];
	for (int j = 0; j < size; j++)
	{
		primes[j] = array[j];
	}
	num_primes = size;
	get_factors(i, array);
	std::cout << 1;
	for (int j = 0; j < num_primes; j++)
	{
		if (array[j] > 1)
			std::cout << ", " << primes[j] << "^" << array[j];
		else if (array[j] == 1)
			std::cout << ", " << primes[j];
	}
	std::cout << std::endl;
}

unsigned get_factors(const unsigned num, unsigned array[])
{
	for (int i = 0; i < num_primes; i++)
	{
		array[i] = 0;
	}
	int curr_prime = primes[0];
	int dividend = num;
	for (int i = 0; i < num_primes;)
	{
		if (curr_prime == dividend)
		{
			array[i]++;
			break;
		}
		else if (curr_prime <= dividend)
		{
			if (dividend % curr_prime == 0)
			{
				dividend /= curr_prime;
				array[i]++;
			}
			else
			{
				i++;
				curr_prime = primes[i];
			}
		}
		else
			break;
	}
}

void get_primes_bel(const unsigned bound, unsigned array[], unsigned& size)
{
	size = 0;
	bool isnt_prime[bound]{false};
	isnt_prime[0] = true;
	for (int i = 1; i < bound; i++)
	{
		if (!isnt_prime[i])
		{
			array[size] = i + 1;
			size++;
			for (int j = square(i + 1); j <= bound; j += i + 1)
			{
				isnt_prime[j - 1] = true;
			}
		}
	}
}
