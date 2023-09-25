#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class ComplexNumber {
private:
	double actualPart;
	double imaginaryPart;
	string arifmeticOperation;
	bool checkArifmeticOperation(const string  &);
public:
	ComplexNumber();
	ComplexNumber(double , double , const string& );
	ComplexNumber(const ComplexNumber& );
	~ComplexNumber() {};
	void setActualPart(double);
	void setImaginaryPart(double);
	void setArifmeticOperation(const string&);
	double getActualPart() const;
	double getImaginaryPart() const;
	string  getArifmeticOperation() const;
};

