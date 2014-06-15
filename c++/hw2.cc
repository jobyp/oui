#include <iostream>
#include <thread>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

class X {

public:
	X(unsigned _i) : i( _i) {}
	
	void hello()
	{ 
		std::string s = "[" + std::to_string( i) + "] Hello, world\n";
		std::cout << s;
		i *= 10;
	}

	void hello() const
	{ 
		std::string s = "[" + std::to_string( i) + "] Hello, world\n";
		std::cout << s;
	}


private:
	unsigned i;
};

int main()
{
	std::vector<X> xs;
	std::vector<std::thread> ts;
	
	typedef void (X::*p_hello) ();
	p_hello hello = &X::hello;

	typedef void (*p_hello2) (X*);

	for(unsigned i = 0; i < 10; i++)
		xs.push_back( X( i));

	for(auto& x : xs)
		ts.push_back( std::thread( hello, &x));
	
	std::for_each( ts.begin(), ts.end(), std::mem_fn( &std::thread::join));
	
	for(auto& x : xs)
		reinterpret_cast<p_hello2>(hello)(&x);

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
