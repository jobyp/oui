#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cassert>

#ifdef NDEBUG
#undef NDEBUG
#endif

//template <typename T>
void merge(unsigned A[], const std::size_t p, const std::size_t q, const std::size_t r, unsigned B[])
{
	std::size_t i = p;
	std::size_t j = q + 1;
		
	for(std::size_t k = p; k <= r; k++) {
		
		if ( i <= q && 
		     j <= r && 
		     A[i] <= A[j]) {
			
			B[k] = A[i];
			i++;
		} 
		else if ( i <= q && 
			  j <= r) { 
			
			B[k] = A[j];
			j++;
		}
		else {
			
			while( i <= q) 
				B[k++] = A[i++];
			
			while( j <= r)
				B[k++] = A[j++];
		}
	}
		

	for(std::size_t i = p; i <= r; i++)
		A[i] = B[i];
}

void merge_sort_aux(unsigned A[], const std::size_t p, const std::size_t r, unsigned B[])
{
	if (p == r)
		return;
	
	std::size_t q = (p + r) / 2;

	merge_sort_aux(A, p, q, B);
	merge_sort_aux(A, q + 1, r, B);
	
	merge(A, p, q, r, B);
	return;
}

void merge_sort(unsigned A[], const std::size_t len)
{
	unsigned *B = new unsigned [len];
	
	merge_sort_aux(A, 0, len - 1, B);

	delete[] B;
	return;
}

int main()
{
	std::vector<unsigned> nums;

	unsigned i;
	while( std::cin >> i)
		nums.push_back( i);

	std::size_t len = nums.size();
	
	unsigned *A = new unsigned[len];

	for(std::size_t j = 0; j < len; j++)
		A[j] = nums[j];

	merge_sort( A, len);

	for(std::size_t j = 0; j < len; j++)
		std::cout << A[j] << " ";
	std::cout << std::endl;
	
	delete[] A;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
