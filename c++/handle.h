#ifndef __HEADER__HANDLE__H_
#define __HEADER__HANDLE__H_

#include <stdexcept>

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

#endif

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
