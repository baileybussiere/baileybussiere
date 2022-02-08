#include <iostream>

using namespace std;

unsigned long int gridpaths(int, int);

unsigned long int gridpath_cache[19][19];

int main()
{
	int n;
	cout << "This program calculates the number of grid paths for a n*n grid." << endl << "Please enter n: ";
	cin >> n;
	if (n == 0)
		cout << 0 << endl;
	else
		cout << gridpaths(n, n) << endl;
}

unsigned long int gridpaths(int n, int m)
{
	if (gridpath_cache[n - 1][m - 1] != 0)
		return gridpath_cache[n - 1][m - 1];
	else if (n == 1)
	{
		gridpath_cache[n - 1][m - 1] = m + 1;
		return m + 1;
	}
	else
	{
		int n1 = n - 1;
		int m1 = m - 1;
		unsigned long gp = gridpaths((n1 <= m)? n1: m, (n1 <= m)? m: n1) + gridpaths((n <= m1)? n: m1, (n <= m1)? m1: n);
		gridpath_cache[n - 1][m - 1] = gp;
		return gp;
	}
}
