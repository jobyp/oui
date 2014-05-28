#ifndef __HEADER_STR2__H_
#define __HEADER_STR2__H_

#include <iostream>

#include "handle.h"
#include "vec.h"

template <typename T>
class Str {
	
public:
	Str() : data( new Vec<char>) {}

private:
       
	Ptr< Vec<char> > data;

};


#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
