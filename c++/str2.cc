#include <iostream>

#include "str2.h"

using std::cout;
using std::endl;

int main()
{
	Str s1("Joby");
	Str s2(" Poriyath");

	Str s3(s1 + s2);

	Str s4(s3.begin(), s3.end());
	
	cout << s4 + ": C++ is fun" << endl;
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
