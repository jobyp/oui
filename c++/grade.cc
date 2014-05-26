#include <stdexcept>
#include <vector>

#include "median.h"
#include "grade.h"


using std::vector;
using std::domain_error;

double grade(double midterm, double final, double homework)
{
	return ( 0.2 * midterm +
		 0.4 * final +
		 0.4 * homework);
}

double grade(double midterm, double final, const vector<double>& hw)
{
	if ( hw.size() == 0)
		throw domain_error("student didn't submit any homework grades");

	return grade( midterm, final, median( hw));
}
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
