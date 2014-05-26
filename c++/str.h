#ifndef __HEADER_STR__H_
#define __HEADER_STR__H_

#include <algorithm>
#include <iterator>
#include <cstring>
#include "vec.h"

class Str {
public:
	typedef Vec<char>::size_type size_type;
	typedef Vec<char>::iterator iterator;
	typedef Vec<char>::const_iterator const_iterator;
	
	Str() {}
	Str(size_type n, char c) : data( n + 1, c) { data[n + 1] = '\0'; }
	Str(const char* cp) 
	{ 
		std::copy( cp, cp + strlen( cp), std::back_inserter( data));  
		data.push_back( '\0');
	}
	
	template <typename In>
	Str(In b, In e) : data( b, e) { data.push_back( '\0'); }

	void clear() { data.clear(); }

	size_type size() const 
	{ 
		size_type n = data.size(); 
		if ( n > 0)
			return n - 1;
		else
			return n;
	}
	
	iterator begin() { return data.begin(); }
	const_iterator begin() const { return data.begin(); }
	iterator end() { return data.end(); }
	const_iterator end() const { return data.end(); }

	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }

	

	friend std::istream& operator>>(std::istream& in, Str& s);

	Str& operator+=(const Str& s)
	{
		if ( ( s.size() > 0) && ( size() > 0)) {

			data[size()] = s[0];
			std::copy( s.begin() + 1, s.end(), std::back_inserter( data));
		}
		else
			std::copy( s.begin(), s.end(), std::back_inserter( data));
		return *this;
	}

	const char* c_str() const { return data.begin(); }

private:
	Vec<char> data;
};

std::ostream& operator<<(std::ostream& out, const Str& s);
Str operator+(const Str& l, const Str& r)
{
	Str sum(l);
	sum += r;
	return sum;
}

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
