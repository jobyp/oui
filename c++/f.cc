#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <algorithm>

#include "split.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::back_inserter;
using std::sort;
using std::ostream_iterator;
using std::istream_iterator;
using std::list;

template <class In, class Out>
Out p_copy(In begin, In end, Out dest)
{
	while( begin != end) 
		*dest++ = *begin++;

	return dest;
}

template <class X>
void print_vector(const vector<X>& v)
{
	for(const auto& x: v)
		cout << x << " ";
	cout << endl;
}

template <class For, class X>
void p_replace(For begin, For end, const X& x, const X& y)
{
	while( begin != end) {
		
		if ( *begin == x)
			*begin = y;
		++begin;
	}
}

template <class X>
void p_swap(X& x, X& y)
{
	X tmp(x);

	x = y;
	y = tmp;
}

template <class Bi>
void p_reverse(Bi begin, Bi end)
{
	while ( begin != end) {
		
		--end;
		
		if ( begin != end)
			p_swap( *begin++, *end);
	}
}

template <class Ran, class X>
Ran p_bin_search(Ran begin, Ran end, const X& x)
{
	Ran not_found = end;

	while( begin != end) {
		
		Ran mid = begin + (end - begin) / 2;

		if ( x < *mid ) 
			end = mid;
		else if ( *mid < x)
			begin = mid + 1;
		else
			return mid;
	}
	
	return not_found;
}

template <class T1, class T2>
bool p_equal(T1 b, T1 e, T2 b2)
{
	while( b != e && *b++ == *b2++)
		;

	if ( b == e)
		return true;
	else
		return false;
}

template <class T, class X>
T p_find(T b, T e, const X& x)
{
	while( b != e && *b != x)
		++b;

	return b;
}

template <class In, class Out, class F>
Out p_remove_copy_if(In b, In e, Out d, F pred)
{
	while( b != e) {
		
		if ( !pred( *b)) 
			*d++ = *b;
		b++;
	}
	
	return d;
}

template <class In, class Out, class F>
Out p_transform(In b, In e, Out d, F f)
{
	while( b != e)
		*d++ = f( *b++);
	
	return d;
}

bool is_equal(const string& x, const string& y) { return (x == y); }

template <class T, class X>
X p_accumulate(T b, T e, X x)
{
	while( b != e) 
		x += *b++;

	return x;
}

template <class T1, class T2>
bool p_startswith(T1 b1, T1 e1, T2 b2, T2 e2)
{
	while( b1 != e1 && 
	       b2 != e2 && 
	       *b1++ == *b2++)
		;
		
	return (b2 == e2);
}

template <class T1, class T2>
T1 p_search(T1 b, T1 e, T2 b2, T2 e2)
{
	while( b != e &&
	       !( p_startswith( b++, e, b2, e2)))
		;

	return b;
} 

template <class T, class F>
T p_find_if(T b, T e, F f)
{
	while( b != e && ! f( *b))
		b++;
	return b;
}

template <class T, class X>
T p_remove(T b, T e, const X& x)
{
	while ( b != e) {

		T i = p_find( b, e, x);
		T j = p_find_if( i, e, [&] (const X& y) { return (x != y); });
	
		// If all elements are NOT EQUAL to x in the range [b, e)
		if (i == e)
			return i;
		
		// If all elements are EQUAL to x in the range [b, e)
		if (j == e)
			return i;

		p_swap( *i, *j);
		b = ++i;
	} 
	
	return b;
}

template <class T, class F>
T p_remove_if(T b, T e, F pred)
{
	while ( b != e) {

		T i = p_find_if( b, e, pred);
		
		T j = i;
		while( j != e && !pred( *j))
			++j;
		
		// If all elements are NOT EQUAL to x in the range [b, e)
		if (i == e)
			return i;
		
		// If all elements are EQUAL to x in the range [b, e)
		if (j == e)
			return i;

		p_swap( *i, *j);
		b = ++i;
	} 
	
	return b;
}

template <class T, class F>
T p_partition(T b, T e, F pred)
{
	while ( b != e) {

		T i = b;

		// Find the first element that failed the predicate
		while ( i != e && pred( *i))
			++i;

		T j = i;		
		// Find the first element that passed the predicate

		while( j != e && !pred( *j))
			++j;
		
		if (i == e)
			return i;
		
		if (j == e)
			return i;

		p_swap( *i, *j);
		b = ++i;
	} 
	
	return b;
}



int main(int argc, char **argv)
{
	vector<unsigned> nums;

	copy(istream_iterator<unsigned>(cin),
	     istream_iterator<unsigned>(),
	     back_inserter(nums));
	
	auto odd = [] (unsigned x) { return (x % 2 == 1); };

	p_partition(nums.begin(), nums.end(), odd);

	copy(nums.begin(), nums.end(),
	     ostream_iterator<unsigned>(cout, "\n"));
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
