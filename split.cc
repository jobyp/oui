#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::vector;
using std::string;
using std::isspace;

vector<string> split(const string& s)
{
	vector<string> result;
	string::size_type i = 0;

	while(i != s.size()) {
		
		// skip leading whitespace chars
		while(( i != s.size()) && isspace( s[i]))
			i++;
		
		string::size_type j = i;
		
		while(( j != s.size()) && !isspace( s[j]))
			j++;
		      
		if (i != j) {
			result.push_back( s.substr( i, j - i));
			i = j;
		}
	}

	return result;
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
