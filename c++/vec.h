#ifndef __HEADER_VEC__H_
#define __HEADER_VEC__H_

#include <cstdlib>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iterator>

using std::cout;
using std::endl;

#define f_name() { cout << __PRETTY_FUNCTION__  << endl; }


template <typename T>
class Vec {
public:
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* iterator;
	typedef const T* const_iterator;

	Vec() { create(); }
	explicit Vec(size_type n, const T& val = T()) { create( n, val); }
	Vec(const_iterator b, const_iterator e) { create( b, e); }
	Vec(const Vec& v) { create( v.begin(), v.end()); }
	
	~Vec() { uncreate(); }
	
	Vec& operator[](size_type i) { return data[i]; }
	const Vec& operator[](size_type i) const { return data[i]; }
	Vec& operator=(const Vec& rhs);

	iterator begin() { return data; }
	const_iterator begin() const { return data; }
	iterator end() { return avail; }
	const_iterator end() const { return avail; }
	size_type size() const { return ( avail - data); }

	Vec& push_back(const T& val) 
	{
		if ( avail == limit)
			grow();

		unchecked_append(val);
		
		return *this;
	}

	iterator erase(iterator i)
	{
		if ( i + 1 == avail) { // Case 1. i points to last element
			
			alloc.destroy( i);
			avail--;
			return avail;
		}
		else // Case 2. i points to any other element than last
			return shrink( i, i + 1);
	}

	iterator erase(iterator b, iterator e)
	{
		if (b != e)
			return shrink( b, e);
		else
			return e;
	}

	void clear() { uncreate(); }
	
private:
	iterator data;
	iterator avail;
	iterator limit;

	std::allocator<T> alloc;

	void create();
	void create(size_type n, const T& val);
	void create(const_iterator b, const_iterator e);

	void uncreate();

	void grow();
	void unchecked_append(const T& val);

	iterator shrink( iterator b, iterator e);
};

template <typename T>
typename Vec<T>::iterator Vec<T>::shrink(iterator b, iterator e)
{
	Vec<T> v1( data, b);
	Vec<T> v2( e, avail);

	uncreate();

	create( v1.begin(), v1.end());
	
	typename Vec<T>::iterator i = v2.begin();
	while( i != v2.end())
		push_back( *i);

	return avail;
}

template <typename T>
void Vec<T>::grow()
{
	typename std::allocator<T>::size_type n = std::max( limit - data, std::ptrdiff_t( 1)) * 2;
	
	iterator new_data = alloc.allocate( n);
	iterator new_avail = std::uninitialized_copy( begin(), end(), new_data);
	
	uncreate();

	data = new_data;
	avail = new_avail;
	limit = data + n;
}

template <typename T>
void Vec<T>::unchecked_append(const T& val)
{
	// cout << __PRETTY_FUNCTION__  << endl;
	
	alloc.construct( avail++, val);
}


template <typename T>
void Vec<T>::create() { data = avail = limit = nullptr; }

template <typename T>
void Vec<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);
	avail = limit = data + n;
	
	std::uninitialized_fill( data, avail, val);
	
	return;
}


template <typename T>
void Vec<T>::create(const_iterator b, const_iterator e)
{
	typename std::allocator<T>::size_type n = e - b;
	
	if ( n == 0) {
		
		data = avail = limit = nullptr;
		return;
	}
	
	data = alloc.allocate(n);
	limit = avail = std::uninitialized_copy( b, e, data);

	return;
}

template <typename T>
void Vec<T>::uncreate() 
{
	typedef typename std::allocator<T>::size_type alloc_size_type;

	if (data != nullptr) {
		
		iterator i = avail;

		while( i != data) 
			alloc.destroy(--i);
		
		alloc.deallocate( data, alloc_size_type( limit - data));
	}
	
	data = avail = limit = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& rhs)
{
	if ( this != &rhs) {
		
		uncreate();
		create( rhs.begin(), rhs.end());
	}

	return *this;
}

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
