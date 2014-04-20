#include <vector>
#include <numeric>

#include "median.h"

using std::vector;
using std::accumulate;

double average(const vector<double>& v)
{
	return accumulate( v.begin(), v.end(), 0.0) / v.size();
}


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
