#include "vec.h"

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

	cout << "Vec<int> v_i is created" << endl;
	return v_i.size();
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
