#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::map;

int main()
{
	string s;
	map<string, int> counters;

	while( cin >> s)
		++counters[s];

	for( map<string, int>::const_iterator it = counters.begin();
	     it != counters.end();
	     ++it)
		cout << it->first << "\t" << it->second << endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
