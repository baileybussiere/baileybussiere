#include <string>
#include <vector>

using namespace std;

class entry
{
public:
	string head;
	string trans;
	int pos; //0 noun, 1 verb, 2 numeral, 3 emotive, 4 function

	string print();
}