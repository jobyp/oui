#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "split.h"
#include "xref.h"

using std::map;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main()
{
	map< string, vector< unsigned > > refs = xref( cin);

	for(map< string, vector< unsigned > >::const_iterator it = refs.begin();
	    it != refs.end();
	    ++it) {

		cout << it->first << " occurs on lines: ";
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
