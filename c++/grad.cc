#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

#include "grad.h"
#include "grade.h"

using std::string;
using std::istream;
using std::min;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::streamsize;
using std::domain_error;
using std::max;
using std::setprecision;

istream& read_hw(istream& in, vector<double>& hw)
{
	if ( !in)
		return in;

	hw.clear();

	double x;
	while ( in >> x)
		hw.push_back(x);

	in.clear();

	return in;
}

double Core::grade() const 
{
	return ::grade( midterm, final, homework);
}

istream& Core::read_common(istream& in)
{
	in >> n >> midterm >> final;
	return in;
}

istream& Core::read(istream& in)
{
	read_common( in);
	read_hw( in, homework);
	return in;
}

istream& Grad::read(istream& in)
{
	read_common( in);
	in >> thesis;
	read_hw( in, homework);
	return in;
}

double Grad::grade() const 
{
	return min( Core::grade(), thesis);
}

int main()
{
	vector<Student_info> students;
	Student_info record;
	string::size_type maxlen = 0;

	while( record.read( cin)) {

		maxlen = max( maxlen, record.name().size());
		students.push_back( record);
	}

	sort( students.begin(), students.end(), Student_info::compare);

	for(auto& s : students) {

		cout << s.name() 
		     << string( maxlen + 1 - s.name().size(), ' ');
		
		try {

			double final_grade = s.grade();
			streamsize prec = cout.precision();
			cout << setprecision( 3) << final_grade
			     << setprecision( prec) << endl;
		} catch ( domain_error e) {
			
			cout << e.what() << endl;
		}
	}

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
