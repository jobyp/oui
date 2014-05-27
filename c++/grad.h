#ifndef __HEADER__GRAD__H_
#define __HEADER__GRAD__H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "handle.h"

class Core {

public:

	Core(): midterm(0), final(0) {}
	Core(std::istream& in) { read( in); }
	std::string name() const { return n; }
	virtual std::istream& read(std::istream&);
	virtual double grade() const;
	
	virtual ~Core() {};

	virtual Core* clone() const { return new Core( *this); } 
	
protected:
	std::istream& read_common(std::istream&);
	double midterm, final;
	std::vector<double> homework;

private:
	std::string n;
};

class Grad: public Core {

public:
	Grad() : Core(), thesis(0) {}
	Grad(std::istream& in) { read( in); }
	~Grad() {}

	double grade() const;
	std::istream& read(std::istream&);
	
	Grad* clone() const { return new Grad( *this); } 

private:
	double thesis;
};

// bool compare(const Core&, const Core&);

class Student_info {

public:
	Student_info() : cp(nullptr) {}
	Student_info(std::istream& in) : cp(nullptr) { read( in); }
	
	std::string name() const
	{
		if ( !cp)
			throw std::runtime_error("uninitialized student object");
		return cp->name();

	}

	double grade() const
	{
		if ( !cp)
			throw std::runtime_error("uninitialized student object");
		return cp->grade();
	}

	std::istream& read(std::istream& in)
	{
		if ( !in)
			return in;

		char s_type;

		in >> s_type;
		if ( s_type == 'U')
			cp = Ptr<Core> ( new Core( in));
		else if ( s_type == 'G')
			cp = Ptr<Core> ( new Grad( in));

		return in;
	}
	
	static bool compare(const Student_info& s1,
			    const Student_info& s2)
	{
		return s1.name() < s2.name();
	}

private:
	Ptr<Core> cp;
};

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
