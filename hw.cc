#include <iostream>

int main()
{
	std::string hw { "Hello, World\n" };
	std::cout << hw;
	
	return 0;
}

// Local Variables:
// c-basic-offset: 8
// End:


/*
  Chapter 1.
  
  The semantics of argument passing are identical to the semantics of 
  copy initialization. 

  CHECKME: What's copy initialization?

  If two functions are defined with the same name but different argument
  types, compiler will choose the most appropriate function to invoke 
  for each call. If two alternative functions could be called, but 
  neither is better than the other other, the call is deemed ambiguous
  and the compiler gives an error.
  
  Fundamental types : bool, char, int, double, unsigned.
  
  Some bitwise operators : x^y (x-or), ~x (not)

  CHECKME: How do I make compiler warn incase of type conversion with
  data loss ? e.g. double -> int

  int i {7.2}; // results in an error -- hence preferred.

  const, constexpr

  For a function to be usable in a constant expression, that is, in an
  expression that will be evaluated by the compiler, it must be defined
  constexpr. e.g 
  
          constexpr double square(double d) { return d * d; }
  
  range-for-statement

          for(auto x : v) { foo(x); }
	  for(auto& x: v) { ++x; }
  
  A reference is similar to a pointer, except that you don't need to use
  a prefix * to access the value referred to by the reference. Also a
  reference cannot be made to refer to a different object after its
  initialization.
  
  CHECKME: errata (pg 11: count_x())

  Chapter 2. User defined types
  
  string 
  
  string s; string t; s + t; s.size(); string s(10, 'p');

 */
