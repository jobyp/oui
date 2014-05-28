#include <iostream>
#include <thread>
#include <stdexcept>

using std::cout;
using std::endl;
using std::thread;

void hello()
{
	cout << "Hello, world" << endl;
}

int main()
{
	thread t(hello);
	t.join();
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
