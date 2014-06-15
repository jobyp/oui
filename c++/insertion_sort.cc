#include <iostream>
#include <vector>


template <typename T>
void insertion_sort(std::vector<T> &elems)
{
	typename std::vector<T>::size_type n = elems.size();

	for(std::size_t i = 1; i < n; i++) {
		
		T curr = elems[i];
		
		std::size_t j = i - 1;
		while( j >= 0 && elems[j] > curr) {

			elems[j + 1] = elems[j];
			j--;
		}
		elems[j + 1] = curr;
	}

	return;
}

int main()
{
	std::vector<unsigned> nums;
	unsigned n;
	
	while(std::cin >> n)
		nums.push_back( n);

	insertion_sort( nums);
	
	for( const auto& i : nums)
		std::cout << i << std::endl;

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
