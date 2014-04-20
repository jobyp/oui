#ifndef __HEADER_SPLIT__H_
#define __HEADER_SPLIT__H_

#include <vector>
#include <string>
#include <algorithm>

bool is_space(char c);

bool not_space(char c);

std::vector<std::string> split(const std::string& s);

template <class Out>
void split(const std::string& s, Out dest)
{
	using std::string;
	using std::find_if;

	string::const_iterator i = s.begin();
	
	while( i != s.end()) {

		i = find_if( i, s.end(), not_space);
		
		string::const_iterator j = find_if( i, s.end(), is_space);

		if ( i != j) {
			
			*dest++ = string(i, j);
			i = j;
		}
	}

	return;
}

#endif

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
