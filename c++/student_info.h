#ifndef __HEADER_STUDENT_INFO__H_
#define __HEADER_STUDENT_INFO__H_

#include <vector>
#include <string>
#include <iostream>

class Student_info {
private:
	std::string _name;
	double midterm;
	double final;
	std::vector<double> homework;

public:
	Student_info() : midterm( 0), final( 0) {};
	Student_info(std::istream& in) { read( in); };
	std::istream& read(std::istream&);
	double grade() const;
	std::string name() const { return _name; }
	bool valid() const { return !homework.empty(); }
};

std::istream& read_hw(std::istream& in, std::vector<double>& hw);
bool compare_student_info(const Student_info& x, const Student_info& y);
bool fgrade(const Student_info& s);
bool pgrade(const Student_info& s);


#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
