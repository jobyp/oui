#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::max;
using std::vector;
using std::string;

string::size_type width(const vector<string>& v)
{
	string::size_type maxlen = 0;

	for(vector<string>::size_type i = 0; i != v.size(); i++)
		maxlen = max(maxlen, v[i].size());

	return maxlen;
}

vector<string> frame(const vector<string>& v, string::size_type w)
{
	vector<string> ret;
	
	ret.push_back(string(2 + w + 1 + 1, '*'));

	for(vector<string>::size_type i = 0; i != v.size(); i++)
		ret.push_back( "* " + v[i] + string(w + 1 - v[i].size(), ' ') + "*"); 
		      
	ret.push_back(string(2 + w + 1 + 1, '*'));

	return ret;
}

vector<string> vcat(const vector<string>& top, const vector<string>& bottom)
{
	vector<string> ret = top;
	
	ret.insert( ret.end(), bottom.begin(), bottom.end());

	return ret;
}

vector<string> hcat(const vector<string>& left, const vector<string>& right)
{
	vector<string> ret;
	
	string::size_type l_width = width( left);

	vector<string>::size_type l_height = left.size();
	vector<string>::size_type r_height = right.size();

	vector<string>::size_type height = max(l_height, right.size());
	
	string l_spaces = string( l_width, ' ');
	
	for( vector<string>::size_type i = 0; i != height; i++) {
		
		string l = ( i < l_height) ? 
			left[i] + string( l_width - left[i].size(), ' ') : l_spaces;
		string r = ( i < r_height) ? right[i] : "";
		
		ret.push_back( l + r);
	}

	return ret;
}

int main()
{
	string  l;
	vector<string> lines;

	while( getline( cin, l))
		lines.push_back( l);
	
	vector<string> pic = frame( lines, width( lines));
	
	vector<string> vpic = vcat( pic, pic);
	
	vector<string> hpic = hcat( pic, vpic);
	
	for(const auto& s: hpic)
		cout << s << endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
