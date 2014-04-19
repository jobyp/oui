#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <iterator>

#include "median.h"

using std::vector;
using std::sort;
using std::domain_error;
using std::accumulate;
using std::remove_copy;
using std::back_inserter;

double median(vector<double> vec)
{
	typedef vector<double>::size_type vec_size;
	vec_size size = vec.size();
	
	if (size == 0)
		throw domain_error("median of empty vector");

	sort(vec.begin(), vec.end());

	vec_size mid = size / 2;
	return (size % 2 == 0) ? (vec[mid - 1] + vec[mid]) / 2 : vec[mid];
}

double average(const vector<double>& v)
{
	return accumulate( v.begin(), v.end(), 0.0) / v.size();
}


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
