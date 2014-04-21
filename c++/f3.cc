#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::map;

class Foo {
	unsigned _n;
	string _name;

public:
	Foo() {};
	Foo(unsigned x) : _n(x) {};
	Foo(const string& s) : _n(0), _name(s) {};
	Foo(unsigned x, const string& s) : _n(x), _name(s) {};
	unsigned n() const { return _n; };
	string name() const { return _name; };
};


int main()
{
	map<unsigned, Foo> foo;

	cout << Foo().n() << endl;
	cout << foo.begin()->second.n() << endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
