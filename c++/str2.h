#ifndef __HEADER_STR2__H_
#define __HEADER_STR2__H_

#include <iostream>
#include <algorithm>
#include <cstring>
#include <iterator>

#include "handle.h"
#include "vec.h"

template <>
Vec<char>* clone(const Vec<char>* vp)
{
	return new Vec<char>( *vp);
}

class Str {
	
	friend std::istream& operator>>(std::istream&, Str&);

public:
	typedef Vec<char>::size_type size_type;
	typedef Vec<char>::iterator iterator;
	typedef Vec<char>::const_iterator const_iterator;

	Str() : data( new Vec<char>) {}

	Str(const char* cp) : data( new Vec<char>) 
	{
		std::copy( cp, cp + std::strlen( cp), std::back_inserter( *data));
	}

	Str(size_type n, char c) : data( new Vec<char>( n, c)) {}
	
	template <typename In>
	Str(In b, In e) : data( new Vec<char>) 
	{
		std::copy( b, e, std::back_inserter( *data));
	}

	Str& operator+=(const Str& rhs)
	{
		data.make_unique();
		std::copy( rhs.data->begin(), rhs.data->end(),
			   std::back_inserter( *data));
		return *this;
	}

	iterator begin() { return data->begin(); }
	const_iterator begin() const { return data->begin(); }
	
	iterator end() { return data->end(); }
	const_iterator end() const { return data->end(); }
	
	size_type size() const { return data->size(); }

	char& operator[](size_type i) 
	{
		data.make_unique();
		return (*data)[i];
	}
	
	const char& operator[](size_type i) const
	{
		return (*data)[i];
	}

private:
       
	Ptr< Vec<char> > data;
};

std::istream& operator>>(std::istream& in, Str& s)
{
	s.data->clear();

	if ( !in)
		return in;
	
	char c;
	while ( in.get( c) && std::isspace( c))
		;

	if ( in)
		s.data->push_back( c);

	while ( in.get( c) && ! std::isspace( c))
		s.data->push_back( c);

	if ( in)
		in.unget();
	
	return in;
}


std::ostream& operator<<(std::ostream& out, const Str& s)
{
	for(Str::const_iterator i = s.begin();
	    i != s.end();
	    i++)
		out << *i;
	return out;
}

Str operator+(const Str& s1, const Str& s2)
{
	Str s(s1);
	s += s2;
	return s;
}

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
