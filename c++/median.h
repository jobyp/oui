#ifndef __HEADER_MEDIAN__H_
#define __HEADER_MEDIAN__H_

#include <vector>
#include <algorithm>
#include <stdexcept>

template <class T>
T median(std::vector< T > vec)
{
	using std::sort;
	using std::vector;
	using std::domain_error;

	typedef typename vector< T >::size_type vec_size;
	vec_size size = vec.size();
	
	if (size == 0)
		throw domain_error("median of empty vector");

	sort(vec.begin(), vec.end());

	vec_size mid = size / 2;
	return (size % 2 == 0) ? (vec[mid - 1] + vec[mid]) / 2 : vec[mid];
}

double average(const std::vector<double>& v);

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
