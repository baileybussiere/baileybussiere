#include <iostream>
#include <string>

/*
Executes the function pointed to by 'to_try' on the passed args
until the funtion pointed to by 'test' returns true on the passed args.
Each time the test fails, the string returned by 'message_when_loop'
executed on the passed args is printed to the screen.
*/

template<typename... Args>
void try_until(Args&... args, void (*to_try)(Args&... args), bool (*test)(const Args&... args), std::string (*message_when_loop)(const Args&... args))
{
	to_try(args...);
	while(!test(args...))
	{
		std::cout << message_when_loop(args...);
		to_try(args...);
	}
}
//Below is a triplet of test functions
void func1(int &num)
{
	std::cout << "Please enter a number from 0 to 9:\n";
	std::cin >> num;
}

bool test1(const int &num)
{
	return 0 <= num && num < 10;
}

std::string message1(const int &num)
{
	return "The number " + std::to_string(num) + " is not in the required range.\n";
}

int main()
{
	void (*p_func1)(int&){*func1};
	bool (*p_test1)(const int&){*test1};
	std::string (*p_message1)(const int&){*message1};

	int i = -1;
	try_until<int>(i, p_func1, p_test1, p_message1);
	std::cout << "Finished. The number you entered was " << i;
}
