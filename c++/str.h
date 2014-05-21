#ifndef __HEADER_STR__H_
#define __HEADER_STR__H_

#include <algorithm>
#include <iterator>
#include <cstring>
#include "vec.h"

class Str {
public:
	typedef Vec<char>::size_type size_type;
	
	Str() {}
	Str(size_type n, char c) : data( n, c) {}
	Str(const char* cp) { std::copy( cp, cp + strlen( cp), std::back_inserter( data)); }
	
	template <typename In>
	Str(In b, In e) : data( b, e) {}

	void clear() { data.clear(); }
	size_type size() const { return data.size(); }

	char& operator[](size_type i) { return data[i]; }
	const char& operator[](size_type i) const { return data[i]; }

	friend std::istream& operator>>(std::istream& in, Str& s);

private:
	Vec<char> data;
};

std::ostream& operator<<(std::ostream& out, const Str& s);

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
