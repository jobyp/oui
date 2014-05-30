#include <iostream>
#include <thread>
#include <stdexcept>

using std::cout;
using std::endl;
using std::thread;

void hello()
{
	cout << "Hello, world\n";
}

class thread_guard {

public:
	explicit thread_guard(thread& _t) : t( _t) {}

	~thread_guard() 
	{
		cout << __PRETTY_FUNCTION__ << endl;

		if ( t.joinable())
			t.join();
	}

	thread_guard(const thread_guard&) = delete;
	thread_guard& operator=(const thread_guard&) = delete;
	
private:
	thread& t;
};

int ff()
{
	thread x( hello);
	thread_guard tx( x);

#if 1	
	throw std::runtime_error("murpy's law!");
#endif	
	
	cout << ( x.joinable() ? "true" : "false") << "\n";
	x.join();
	
	return 0;
}

int main()
{
	try {
		ff();
	} catch(...) {
		cout << "oops!\n";
		return 1;
	}
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
