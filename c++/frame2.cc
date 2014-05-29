#include <iostream>
#include <vector>
#include <string>

#include "str2.h"

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::vector;
using std::string;

Str::size_type width(const vector<Str>& v)
{
	Str::size_type maxlen = 0;

	for(vector<Str>::size_type i = 0; i != v.size(); i++)
		maxlen = max(maxlen, v[i].size());

	return maxlen;
}

vector<Str> frame(const vector<Str>& v, Str::size_type w)
{
	vector<Str> ret;
	
	ret.push_back(Str(2 + w + 1 + 1, '*'));

	for(vector<Str>::size_type i = 0; i != v.size(); i++)
		ret.push_back( "* " + v[i] + Str(w + 1 - v[i].size(), ' ') + "*"); 
		      
	ret.push_back(Str(2 + w + 1 + 1, '*'));

	return ret;
}

vector<Str> vcat(const vector<Str>& top, const vector<Str>& bottom)
{
	vector<Str> ret = top;
	
	ret.insert( ret.end(), bottom.begin(), bottom.end());

	return ret;
}

vector<Str> hcat(const vector<Str>& left, const vector<Str>& right)
{
	vector<Str> ret;
	
	Str::size_type l_width = width( left);

	vector<Str>::size_type l_height = left.size();
	vector<Str>::size_type r_height = right.size();

	vector<Str>::size_type height = max(l_height, right.size());
	
	Str l_spaces = Str( l_width, ' ');
	
	for( vector<Str>::size_type i = 0; i != height; i++) {
		
		Str l = ( i < l_height) ? 
			left[i] + Str( l_width - left[i].size(), ' ') : l_spaces;
		Str r = ( i < r_height) ? right[i] : "";
		
		ret.push_back( l + r);
	}

	return ret;
}

int main()
{
	string  l;
	vector<Str> lines;

	while( getline( cin, l))
		lines.push_back( l.c_str());
	
	vector<Str> pic = frame( lines, width( lines));
	
	vector<Str> vpic = vcat( pic, pic);
	
	vector<Str> hpic = hcat( pic, vpic);
	
	for(const auto& s: hpic)
		cout << s << endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
