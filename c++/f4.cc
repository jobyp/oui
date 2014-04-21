#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::copy;
using std::strlen;

string letter_grade(double grade)
{
	static const double numbers[] = { 
		97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
	};

	static const char* const letters[] = {
		"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"
	};

	size_t const num_grades = sizeof( numbers) / sizeof (const double);

	for( size_t i = 0; i < num_grades; i++)
		if ( grade >= numbers[ i])
			return letters[i];
	
	return "?\?\?";
}

const char* duplicate_chars(const char* p)
{
	size_t len = strlen( p) + 1;
	
	char* _p = new char[len];
	
	copy( p, p + len, _p);
	
	return _p;
}

int main()
{
	cout << letter_grade(19) << endl;
	
	const char* p = duplicate_chars("Hello, world");
	
	cout << p << endl;
	
	delete[] p;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
