#ifndef __HEADER_REPORT__H_
#define __HEADER_REPORT__H_

#include <vector>
#include <iostream>
#include <string>

#include "student_info.h"

double median_analysis(const std::vector<Student_info>& students);
double average_analysis(const std::vector<Student_info>& students);
double optimistic_median_analysis(const std::vector<Student_info>& students);
void write_analysis( std::ostream& out, 
		     const std::string name,
		     double analysis(const std::vector<Student_info>&),
		     const std::vector<Student_info>& did,
		     const std::vector<Student_info>& didnt);


#endif

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
