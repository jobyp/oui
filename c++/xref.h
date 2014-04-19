#ifndef __HEADER_XREF__H_
#define __HEADER_XREF__H_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "split.h"

std::map< std::string, std::vector< unsigned > > 
xref(std::istream& in, 
     std::vector< std::string > find_words(const std::string& l) = split);

std::map< std::string, std::vector< unsigned > > 
xref(const std::vector< std::string >& lines, 
     std::vector< std::string > find_words(const std::string& l) = split);

#endif


// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
