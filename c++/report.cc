#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <string>

#include "report.h"
#include "median.h"
#include "grade.h"
#include "student_info.h"

using std::vector;
using std::transform;
using std::back_inserter;
using std::ostream;
using std::accumulate;
using std::endl;
using std::string;

double median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;

	transform( students.begin(), students.end(),
		   back_inserter( grades), grade_aux);
	
	return median( grades);
}

double average_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	
	transform( students.begin(), students.end(),
		   back_inserter( grades), average_grade);

	return median( grades);
}

static double optimistic_median(const Student_info& s)
{
	vector<double> nonzeros;

	remove_copy( s.homework.begin(), 
		     s.homework.end(), 
		     back_inserter( nonzeros), 
		     0.0);

	if ( nonzeros.empty())
		return grade( s.midterm, s.final, 0.0);
	else
		return grade( s.midterm, s.final, median( nonzeros));
}


double optimistic_median_analysis(const vector<Student_info>& students)
{
	vector<double> grades;
	
	transform( students.begin(), students.end(),
		   back_inserter( grades), optimistic_median);
	
	return median( grades);
}

void write_analysis( ostream& out, 
		     const string name,
		     double analysis(const vector<Student_info>&),
		     const vector<Student_info>& did,
		     const vector<Student_info>& didnt)
{
	out << name << ": median(did) = " << analysis( did)
	    << ", median(didnt) = " << analysis( didnt) 
	    << endl;

	return;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:

