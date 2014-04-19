#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::getline;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

#include "split.h"

int main()
{
	string line;
	vector<string> ss;
	
	while( getline( cin, line)) {
		ss = split( line);
		
		for(const auto& s : ss) 
			cout << "|> " << s << endl;
	}

	return 0;
}
