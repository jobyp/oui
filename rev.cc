#include <iostream>
#include <string>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

string reverse(const string& s)
{
	return string(s.rbegin(), s.rend());
}

int main()
{
	string line;
	while( getline( cin, line))
		cout << reverse( line) << endl;
	
	return 0;
}
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
