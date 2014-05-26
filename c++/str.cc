#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <cctype>

#include "str.h"
#include "vec.h"

std::istream& operator>>(std::istream& in, Str& s)
{
	s.data.clear();
	
	char c;
	while( in.get( c) && isspace( c))
		;

	do 
		s.data.push_back( c);
	while ( in.get( c) && !isspace( c));

	if ( in)
		in.unget();

	return in;
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
	Str s1("Joby");
	Str s2(" Poriyath");

	Str s3(s1 + s2);

	Str s4(s3.begin(), s3.end());
	
	cout << s4 + ": C++ is fun" << endl;

	cout << std::strlen( s1.c_str()) << endl;
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
