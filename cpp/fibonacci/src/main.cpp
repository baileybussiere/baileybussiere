#include <iostream>
#include <cmath>
using namespace std;

long fib_rec(long n)
{
	return n < 2? n: fib_rec(--n) + fib_rec(--n);
}

long fib(long n)
{
	double s5 = sqrt(5);
	double gr = (1 + s5)/2;
	return floor(0.5 + (pow(gr, n) + 1)/s5);
}

int main()
{
	long n;
	cout << "Enter an integer:" << endl;
	cin >> n;
	cout << "Recursive function beginning execution..." << endl;
	cout << fib_rec(n) << endl;
	cout << "Nonrecursive function beginning execution..." << endl;
	cout << fib(n) << endl;
}
