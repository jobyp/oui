#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::accumulate;
using std::getline;

string concat(const vector<string>& v)
{
	return accumulate( v.begin(), v.end(), string());
}

int main()
{
	vector<string> lines;
	string l;
	
	while( getline( cin, l))
		lines.push_back( l);

	cout << "|> " << concat( lines) << endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
