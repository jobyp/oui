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

list<Student_info> extract_fails(list<Student_info>& students)
{
	list<Student_info> fails;

	list<Student_info>::iterator iter = students.begin();

	while(iter != students.end())
		try {
			bool fail = fgrade(*iter);
			if (fail) { 
				fails.push_back(*iter);
				iter = students.erase(iter);
			} else
				++iter;
		} catch (domain_error e) {
			cout << e.what() << endl;
			++iter;
		}
	
	return fails;
}

int main()
{
	// read student records
	Student_info s;
	list<Student_info> students;
	
	while (read(cin, s)) 
		students.push_back(s);

	students.sort(compare_student_info);

	string::size_type maxlen = 0;

	for(list<Student_info>::const_iterator iter = students.begin(); 
	    iter != students.end(); 
	    ++iter)
		maxlen = max(maxlen, iter->name.size());
	
	list<Student_info> failed = extract_fails(students);

	for(list<Student_info>::const_iterator iter = students.begin(); 
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
