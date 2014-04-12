#include <iostream>
#include <stdexcept>

double elem[] = {1,2,3,4,5};
const unsigned elem_sz = sizeof(elem) / sizeof(double);
 
void print()
{
	for(unsigned i = 0; i < sizeof(elem) / sizeof(double); i++)
		std::cout << elem[i] << '\n';

	return;
}

double& ff(double elem[], unsigned sz, unsigned i)
{
	if (i >= sz) 
		throw std::out_of_range{"ff()"};
	else
		return elem[i];
}

int main()
{
	for(unsigned i = 0; i < elem_sz; i++)
		ff(elem, elem_sz, i) += 10;
	print();

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
