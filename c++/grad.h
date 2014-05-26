#ifndef __HEADER__GRAD__H_
#define __HEADER__GRAD__H_

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class Core {

public:

	Core(): midterm(0), final(0) { std::cout << "Core()" << std::endl;}
	Core(std::istream& in) { std::cout << "Core(in)" << std::endl; read( in); }
	std::string name() const { return n; }
	virtual std::istream& read(std::istream&);
	virtual double grade() const;
	
	virtual ~Core() {};
	
protected:
	friend class Student_info;
	
	virtual Core* clone() const { return new Core( *this); } 
	std::istream& read_common(std::istream&);
	double midterm, final;
	std::vector<double> homework;

private:
	std::string n;
};

class Grad: public Core {

public:
	Grad() : Core(), thesis(0) { std::cout << "Grad()" << std::endl;}
	Grad(std::istream& in) { std::cout << "Grad(in)" << std::endl; read( in); }
	~Grad() {}

	double grade() const;
	std::istream& read(std::istream&);
	
protected:
	Grad* clone() const { return new Grad( *this); } 

private:
	double thesis;
};

// bool compare(const Core&, const Core&);

class Student_info {

public:
	Student_info() : cp(nullptr) {}
	Student_info(std::istream& in) : cp(nullptr) { read( in); }
	Student_info(const Student_info&);
	Student_info& operator=(const Student_info&);
	~Student_info() { delete cp; }
	
	std::string name() const
	{
		if ( cp == nullptr)
			throw std::runtime_error("uninitialized student object");
		return cp->name();

	}

	double grade() const
	{
		if ( cp == nullptr)
			throw std::runtime_error("uninitialized student object");
		return cp->grade();
	}

	std::istream& read(std::istream& in)
	{
		if ( !in)
			return in;

		delete cp;

		char s_type;

		in >> s_type;
		if ( s_type == 'U')
			cp = new Core( in);
		else if ( s_type == 'G')
			cp = new Grad( in);

		return in;
	}
	
	static bool compare(const Student_info& s1,
			    const Student_info& s2)
	{
		return s1.name() < s2.name();
	}

private:
	Core* cp;
};

#endif
// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
