#include <iostream>

using std::cout;
using std::endl;

class A {

public:
	A() { cout << "A()" << endl; }
	~A() { cout << "~A()" << endl; }
};

class Base {

public:
	Base() { cout << "Base()" << endl; }
	virtual ~Base() { cout << "~Base()" << endl; }
};

class Derived : public Base {

public:
	Derived() { cout << "Derived()" << endl; }
	~Derived() { cout << "~Derived()" << endl; }

private:
	A a;
};

int main()
{
	Base *b = new Derived();
	delete b;
	return 0;
}


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
