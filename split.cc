#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::isspace;
using std::find_if;

bool is_space(char c) { return isspace( c); }

bool not_space(char c) { return !isspace( c); }

vector<string> split(const string& s)
{
	vector<string> ret;
	string::const_iterator i = s.begin();

	while( i != s.end()) {
		
		i = find_if( i, s.end(), not_space);
				
		string::const_iterator j = find_if( i, s.end(), is_space);
		
		if ( i != j) {
			ret.push_back( string( i, j));
			i = j;
		}
	}

	return ret;
}

int main()
{
	string line;
	vector<string> ss;
	
	while(getline(cin, line)) {
		ss = split(line);
		
		for(const auto& s : ss) 
			cout << "|> " << s << endl;
	}

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
