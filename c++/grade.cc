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

double grade(const Student_info& s)
{
	if (s.homework.size() == 0)
		throw domain_error(s.name + ": homework grades are empty");

	return grade( s.midterm, s.final, median( s.homework));
}

double grade_aux(const Student_info& s)
{
	try {
		return grade( s);
	} 
	catch ( domain_error e) {

		return grade( s.midterm, s.final, 0);
	}
}

double average_grade(const Student_info& s)
{
	return grade( s.midterm, s.final, average( s.homework));
}

bool fgrade(const Student_info& s)
{
	return (grade( s) < 60);
}

bool pgrade(const Student_info& s)
{
	return !fgrade( s);
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
