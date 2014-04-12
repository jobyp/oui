#ifndef __HEADER_STUDENT_INFO__H_
#define __HEADER_STUDENT_INFO__H_

#include <vector>
#include <string>
#include <iostream>

struct Student_info {
	std::string name;
	double midterm;
	double final;
	std::vector<double> homework;
};

std::istream& read_hw(std::istream& in, std::vector<double>& hw);
std::istream& read(std::istream& in, Student_info& s);
bool compare_student_info(const Student_info& x, const Student_info& y);

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
