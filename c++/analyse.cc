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
#include "report.h"

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


int main()
{
	// read student records
	Student_info s;
	vector<Student_info> did, didnt;
	
	while ( s.read( cin)) 
		if ( s.did_all_homework()))
			did.push_back( s);
		else
			didnt.push_back( s);
				
	if ( did.empty()) {
		
		cout << "No student did all homework" << endl;
		return 1;
	}
	
	if ( didnt.empty()) {
		
		cout << "Every student did all homework" << endl;
		return 1;
	}

	write_analysis( cout, "median", median_analysis, did, didnt);
	write_analysis( cout, "average", average_analysis, did, didnt);
	write_analysis( cout, "median of homework turned in",
			optimistic_median_analysis, did, didnt);
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
