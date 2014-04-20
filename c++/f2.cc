#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>

using std::back_inserter;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::copy;
using std::istream;
using std::ostream;
using std::istream_iterator;
using std::ostream_iterator;

ostream& print(ostream& out, const vector<string>& v)
{
	copy( v.begin(), v.end(), ostream_iterator<string>(out, ":"));
	out << endl;
	return out;
}

istream& read(istream& in, vector<string>& ret)
{
	copy(istream_iterator<string>(in), istream_iterator<string>(), back_inserter(ret));
	return in;
}

int main()
{
	vector<string> ret;
	
	read(cin, ret);

	print(cout, ret);

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
