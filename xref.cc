#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "split.h"

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;


map< string, vector< unsigned > > xref(const vector< string >& lines, 
				       vector< string > find_words( const string& l) = split)
{
	map< string, vector< unsigned > > ret;

	for(vector< string >::size_type i = 0; i < lines.size(); i++) {
		
		vector< string > words = find_words( lines[i]);
	
		for(const auto& w : words) 
			ret[w].push_back( i);
		
	}

	return ret;
}

int main()
{
	string l;
	vector< string > lines;

	while( getline( cin, l))
		lines.push_back( l);

	map< string, vector< unsigned > > refs = xref( lines);

	for(map< string, vector< unsigned > >::const_iterator it = refs.begin();
	    it != refs.end();
	    ++it) {

		cout << it->first << ": ";
		cout << it->second[0];

		for(vector< unsigned >::size_type i = 1; i != it->second.size(); i++)
			cout << ", " << it->second[i];
		
		cout << endl;
	}
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
