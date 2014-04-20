#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::ostream_iterator;

#include "split.h"

int main()
{
	string line;
	
	while( getline( cin, line))
		split( line, ostream_iterator<string>( cout, "\n"));

	return 0;
}


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
