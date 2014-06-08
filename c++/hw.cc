#include <thread>
#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <algorithm>
#include <vector>
#include <utility>

using std::cout;
using std::string;
using std::endl;

void hello(unsigned i)
{
	std::cout << "[" << i << "]" << " Hello, world!\n";
	return;
}

void f()
{
	std::vector< std::thread > threads;
	
	for( unsigned i = 0; i < 20; i++) 
		threads.push_back( std::thread( hello, i));

	std::for_each( threads.begin(), threads.end(), std::mem_fn( &std::thread::join));
}

int main()
{
	cout << std::thread::hardware_concurrency() << endl;
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
