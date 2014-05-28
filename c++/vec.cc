#include <iostream>

#include "vec.h"

using std::cout;
using std::endl;

template <typename T>
Vec<T> ff(typename Vec<T>::size_type i)
{
	Vec<T> ret(i);
	
	Vec<T> ret2(ret);
	ret2.push_back( T());

	return ret2;
}

int main()
{
	Vec<int> v_i = ff<int>(2);
	for(int i = 0; i < 10; i++)
		v_i.push_back( i);

	cout << v_i.size() << endl;
	v_i.erase(v_i.begin() + 2, v_i.end());
	cout << v_i.size() << endl;
	v_i.clear();
	cout << v_i.size() << endl;
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
