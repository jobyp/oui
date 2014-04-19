#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>

#include "split.h"
#include "xref.h"

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::set;

map< string, vector< unsigned > > xref(istream& in, 
				       vector< string > find_words(const string& l))
{
	map< string, vector< unsigned > > ret;
	string l;
	unsigned i = 0;
	
	while( getline( in, l)) {

		vector< string > words = find_words( l);
		set< string > unique_words( words.begin(), words.end());
		
		for(const auto& w : unique_words) 
				ret[w].push_back( i);
		
		i++;
	}

	return ret;
}

map< string, vector< unsigned > > xref(const vector< string >& lines, 
				       vector< string > find_words(const string& l))
{
	map< string, vector< unsigned > > ret;

	for(vector< string >::size_type i = 0; i < lines.size(); i++) {
		
		vector< string > words = find_words( lines[i]);
	
		for(const auto& w : words) 
			ret[w].push_back( i);
		
	}

	return ret;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
