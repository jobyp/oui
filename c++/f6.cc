#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::runtime_error;

class A {

public:
	A() {}
	~A() { cout << __PRETTY_FUNCTION__ << endl; }
	
	void operator() () const 
	{
		cout << "Hello, world\n";
	}
};

#define X 1

#if X
int ff()
#else
int main()
#endif
{
	A a;
	a();
	throw runtime_error("murphy's law!");
	return 0;
}

#if X
int main()
{
	try {
		ff();
	} catch(...) {
		cout << "oops!\n";
		throw;
	}
	return 0;
}
#endif

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
