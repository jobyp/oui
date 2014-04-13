#ifndef __HEADER_GRADE__H_
#define __HEADER_GRADE__H_

#include "student_info.h"

double grade(double midterm, double final, double homework);
double grade(const Student_info& s);
double grade_aux(const Student_info& s);
bool fgrade(const Student_info& s);
double average_grade(const Student_info& s);

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
