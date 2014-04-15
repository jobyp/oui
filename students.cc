#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <list>

#include "median.h"
#include "student_info.h"
#include "grade.h"

using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::setprecision;
using std::max;
using std::vector;
using std::sort;
using std::string;
using std::domain_error;
using std::list;
using std::remove_copy_if;
using std::remove_if;
using std::stable_partition;

vector<Student_info> extract_fails(vector<Student_info>& students)
{
	vector<Student_info>::iterator iter = stable_partition( students.begin(), 
								students.end(), 
								pgrade);
	vector<Student_info> fails( iter, students.end());

	students.erase( iter, students.end());
	
	return fails;
}

void print_student_info(const Student_info& s)
{
	cout << s.name << " failed" << endl;
	return;
}

int main()
{
	// read student records
	Student_info s;
	vector<Student_info> students;
	
	while( read( cin, s)) 
		students.push_back( s);
				
	sort( students.begin(), students.end(), compare_student_info);

	string::size_type maxlen = 0;

	for( vector<Student_info>::const_iterator iter = students.begin(); 
	     iter != students.end(); 
	     ++iter)
		maxlen = max(maxlen, iter->name.size());
	
        vector<Student_info> failed = extract_fails(students);
	
	for( const auto& s: failed)
		print_student_info( s);

	for( vector<Student_info>::const_iterator iter = students.begin(); 
	     iter != students.end(); 
	     ++iter)
		try {
			double final_grade = grade(*iter);
			streamsize prec = cout.precision();
			
			cout << iter->name 
			     << string(maxlen + 1 - iter->name.size(), ' ')
			     << ':' << setprecision(3) << final_grade
			     << setprecision(prec) 
			     << endl;
		} catch (domain_error e) {
			cout << e.what() << endl;
		}

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
