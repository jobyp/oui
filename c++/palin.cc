#include <iostream>
#include <string>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::equal;

bool is_palindrome(const string& s)
{
	return equal( s.begin(), s.end(), s.rbegin());
}


int main()
{
	string line;
	while( getline( cin, line))
		if ( is_palindrome( line))
			cout << "Yes" << endl;
		else
			cout << "No" << endl;
	
	return 0;
}
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
