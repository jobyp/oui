#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

#include "student_info.h"
#include "grade.h"
#include "median.h"

using std::istream;
using std::vector;
using std::find;
using std::domain_error;

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

istream& Student_info::read(istream& in)
{
	in >> _name >> midterm >> final;
	read_hw(in, homework);
	return in;
} 

double Student_info::grade() const
{
	if ( !valid())
		throw domain_error(name() + ": homework grades are empty");
	
	return ::grade( midterm, final, median( homework));
}

bool compare_student_info(const Student_info& x, const Student_info& y)
{
	return x.name() < y.name();
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
