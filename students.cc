#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

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

vector<Student_info> extract_fails(vector<Student_info>& students)
{
	vector<Student_info> fails;

	vector<Student_info>::iterator iter = students.begin();

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
	vector<Student_info> students;

	while (read(cin, s))
		students.push_back(s);
	
	sort(students.begin(), students.end(), compare_student_info);

	string::size_type maxlen = 0;

	for(auto& s: students)
		maxlen = max(maxlen, s.name.size());
	
	vector<Student_info> failed = extract_fails(students);

	for(auto& s: students) 
		try {
			double final_grade = grade(s);
			streamsize prec = cout.precision();
			
			cout << s.name 
			     << string(maxlen + 1 - s.name.size(), ' ')
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
