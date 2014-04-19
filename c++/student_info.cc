#include <vector>
#include <iostream>
#include <algorithm>

#include "student_info.h"

using std::istream;
using std::vector;
using std::find;

istream& read_hw(istream& in, vector<double>& hw)
{
	if (!in)
		return in;

	hw.clear();

	double x;
	while (in >> x)
		hw.push_back(x);
	
	in.clear();
	return in;
}

istream& read(istream& in, Student_info& s)
{
	in >> s.name >> s.midterm >> s.final;
	read_hw(in, s.homework);
	return in;
} 

bool compare_student_info(const Student_info& x, const Student_info& y)
{
	return x.name < y.name;
}

bool did_all_homework(const Student_info& s)
{
	return ( find( s.homework.begin(), s.homework.end(), 0) 
		 == s.homework.end());
}


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
