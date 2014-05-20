#include <iostream>
#include <string>
#include <list>

#include "str.h"
#include "vec.h"

std::istream& operator>>(std::istream& in, Str& s)
{
	
}

std::ostream& operator<<(std::ostream& out, const Str& s)
{
	for (Str::size_type i = 0; i < s.size(); i++)
		out << s[i];
	
	return out;
}

using std::cout;
using std::endl;
using std::string;
using std::list;

int main()
{
	Vec<char> vs( 10, 'X');
	Str c( vs.begin(), vs.end());
	
	cout << c.size() << endl;
	cout << c[0] << endl;
	c[0] = 'Z';
	cout << c[0] << endl;
	c.clear();
	cout << c.size() << endl;
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
