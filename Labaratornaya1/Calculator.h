#pragma once
#include "ComplexNumber.h"
class Calculator
{
private:
	ComplexNumber* stackPtr;                      
	int count;     
	int allocated;
	void grow();
	ComplexNumber plus(const ComplexNumber&, const ComplexNumber&);
	ComplexNumber minus(const ComplexNumber&, const ComplexNumber&);
	ComplexNumber multiply(const ComplexNumber&, const ComplexNumber&);
	ComplexNumber division(const ComplexNumber&, const ComplexNumber&);
	int priority(const string&);
public:
	Calculator();
	Calculator(const Calculator& otherStack);
	~Calculator() ;
	void push(const ComplexNumber&);
	ComplexNumber pop();
	void removeAll();     
	ComplexNumber getLastValue() const;
	ComplexNumber getFirstValue() const;
	int getStackSize() const;  
	ComplexNumber* getPtr() const;            
	bool equals(const Calculator& otherStack) const;
	void writeInFile(const string&);
	void getFromFile(const string&);
	ComplexNumber getAnswer();
};

