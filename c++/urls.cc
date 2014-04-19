#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>

#include "urls.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::isalnum;
using std::isalpha;
using std::find;
using std::search;
using std::find_if;
using std::vector;

bool url_character(char c)
{
	static const string url_chars = "~;/?:@=&$-_.+!*'(),";

	return ( isalnum( c) || 
		 find( url_chars.begin(), url_chars.end(), c) != url_chars.end());
}

bool not_url_character(char c)
{
	return !url_character( c);
}

string::const_iterator url_beg(string::const_iterator b, 
			       string::const_iterator e)
{
	static const string sep = "://";
	
	string::const_iterator i = search( b, e, sep.begin(), sep.end());
	if ( i == e) return e;  // didn't find the substring
	
	if ( i + sep.size() == e)  // string ended with '://'
		return e;
	
	// Do we have valid chars after '://' ?
	if ( find_if( i + sep.size(), e, url_character) == e)
		return e;
	
	// Do we have any valid characters before '://'
	if ( i == b)  return e;
	--i;
	if ( !isalpha( *i)) return e;

	while( ( i != b) && ( isalpha( *i)))
		--i;
	++i;
	
	return i;
}

string::const_iterator url_end(string::const_iterator b,
				string::const_iterator e)
{
	return find_if( b, e, not_url_character);
}

vector<string> find_urls(string::const_iterator b,
			 string::const_iterator e)
{
	vector<string> ret;

	while( b != e) {
		
		if ( ( b = url_beg( b, e)) == e) 
			break; // Didn't find any urls

		// So we have at least one URL 
		
		string::const_iterator i = url_end( b, e);

		if ( b != i)
			ret.push_back( string( b, i));

		b = i;
	}
		
	return ret;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
