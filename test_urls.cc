#include <iostream>
#include <string>
#include <vector>

#include "urls.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


void print_urls(const vector<string>& v)
{
	for(const auto& s : v)
		cout << "|> " << s << endl;
	return;
}

int main()
{
	// string line = "google http://www.google.co.uk ";
	// print_urls( find_urls( line.begin(), line.end()));

	string line;
	while( getline( cin, line)) {

		vector<string> urls = find_urls( line.begin(), line.end());
		print_urls( urls);
	}
		
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
