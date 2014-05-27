#ifndef __HEADER__HANDLE__H_
#define __HEADER__HANDLE__H_

#include <stdexcept>
#include <cstring>

template <typename T>
class Handle {

public:
	Handle() : p(nullptr) {}

	Handle(const Handle& s) : p(nullptr) { if ( s.p) p = s.p->clone(); }
	Handle& operator=(const Handle&);
	~Handle() { delete p; }

	Handle(T* t) : p(t) {}

	operator bool() const { return p; }
	T& operator*() const;
	T* operator->() const;

private:

	T* p;
};

template <typename T>
Handle<T>& Handle<T>::operator=(const Handle& rhs)
{
	if ( this != &rhs) {
	
		delete p;
		p = rhs ? rhs.p->clone() : nullptr;
	}
	
	return *this;
}

template <typename T>
T& Handle<T>::operator*() const 
{
	if (p) return *p;
	
	throw std::runtime_error("unbound handle");
}

template <typename T>
T* Handle<T>::operator->() const
{
	if (p) return p;
	
	throw std::runtime_error("unbound handle");
}


template<typename T>
class Ref_handle {

public:
	Ref_handle() : p( nullptr), refptr( new std::size_t( 1)) {}
	Ref_handle(T* p_obj) : p( p_obj), refptr( new std::size_t( 1)) {}

	Ref_handle(const Ref_handle& r) : p( r.p), refptr( r.refptr) { ++*refptr; }

	~Ref_handle() 
	{ 
		--*refptr; 
		if ( *refptr == 0) { 
			
			delete p; 
			delete refptr; 
		}
	}

	Ref_handle& operator=(const Ref_handle& rhs)
	{
		if ( this != &rhs) {
			
			unbind();

			p = rhs.p;
			refptr = rhs.refptr;
			++*refptr;
		}
			
		return *this;
	}

	operator bool() const { return p; }
	
	T& operator*() const
	{
		if ( !p) 
			throw std::runtime_error("unbound Ref_handle");

		return *p;
	}

	T* operator->() const
	{
		if ( !p) 
			throw std::runtime_error("unbound Ref_handle");
	
		return p;
	}

private:

	void unbind() 
	{
		--*refptr; 
		if ( *refptr == 0) { 
			
			delete p; 
			delete refptr; 
		}
	}

	T* p;
	std::size_t* refptr;
};

template<typename T>
class Ptr {

public:
	Ptr() : p( nullptr), refptr( new std::size_t( 1)) {}
	Ptr(T* t) : p( t), refptr( new std::size_t( 1)) {}
	Ptr(const Ptr& rhs) : p( rhs.p), refptr( rhs.refptr) { ++*refptr; }
	
	~Ptr() { unbind(); }

	Ptr& operator=(const Ptr& rhs) 
	{
		if ( this != &rhs) {

			unbind();
			p = rhs.p;
			refptr = rhs.refptr;
			++*refptr;
		}
		return *this;
	}

	operator bool() const { return p; }

	T* operator->() const 
	{
		if ( !p)
			throw std::runtime_error("unbound Ptr");
		return p;
	}

	T& operator*() const
	{
		if ( !p)
			throw std::runtime_error("unbound Ptr");

		return *p;
	}

	void make_unique()
	{
		if ( *refptr != 1) {
			
			unbind();
			
			refptr = new std::size_t( 1);
			p = p ? p->clone() : nullptr;
		}
	}

private:
	
	void unbind()
	{
		--*refptr;
		
		if ( *refptr == 0) {
			
			delete p;
			delete refptr;
		}
	}


	T* p;
	std::size_t* refptr;

} ;

#endif

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
