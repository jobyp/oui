#include <stdexcept>

#include "student_info.h"
#include "median.h"
#include "grade.h"

using std::domain_error;

double grade(double midterm, double final, double homework)
{
	return ( 0.2 * midterm +
		 0.4 * final +
		 0.4 * homework);
}

bool fgrade(const Student_info& s)
{
	return ( s.grade() < 60);
}

bool pgrade(const Student_info& s)
{
	return !fgrade( s);
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
