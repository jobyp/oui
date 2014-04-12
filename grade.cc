#include <stdexcept>

#include "student_info.h"
#include "median.h"

using std::domain_error;

double grade(const Student_info& s)
{
	if (s.homework.size() == 0)
		throw domain_error(s.name + ": homework grades are empty");

	return (0.2 * s.midterm + 0.4 * s.final + 0.4 * median(s.homework));
}

bool fgrade(const Student_info& s)
{
	return (grade(s) < 60);
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
