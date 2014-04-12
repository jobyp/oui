#include <iostream>
#include <string>
#include <stdexcept>

class container {
public:
	virtual double& operator[](unsigned) = 0;
	virtual unsigned size() const = 0;
	virtual ~container() {}
};

void use(container& c)
{
	unsigned sz = c.size();
	
	for(unsigned i = 0; i < sz; i++) {

		std::cout << c[i] << '\n';
	}
	
	return;
}

class vector : public container {
private:
	double* elem;
	unsigned sz;
public:
	vector(unsigned s): elem{new double[s]}, sz{s} {}
	~vector() { delete[] elem; sz = 0; }

	unsigned size() const { return sz; }

	double& operator[](unsigned i);
};

double& vector::operator[](unsigned i)
{
	if (i >= sz) 
		throw std::out_of_range{"vector::operator[]"};
	else
		return elem[i];
}

void populate_vector(vector& v)
{
	for(unsigned i = 0; i < v.size(); i++)
		std::cin >> v[i];

	return;
}

int main(int argc, char* argv[])
{
	unsigned vec_sz = static_cast<unsigned> (atol(argv[1]));
	vector v(vec_sz);
	
	populate_vector(v);
	use(v);
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
