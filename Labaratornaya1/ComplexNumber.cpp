#include "ComplexNumber.h"

ComplexNumber::ComplexNumber() {
	actualPart = 0.0;
	imaginaryPart = 0.0;
}

ComplexNumber::ComplexNumber(double actualPart, double imaginaryPart,
							const string& arifmeticOperation) {
	if (checkArifmeticOperation(arifmeticOperation)) {
		this->arifmeticOperation = arifmeticOperation;
		this->actualPart = actualPart;
		this->imaginaryPart = imaginaryPart;
		
	}
	else {
		this->actualPart = 0.0;
		this->imaginaryPart = 0.0;
	}
}

ComplexNumber::ComplexNumber(const ComplexNumber& complexNum) {
	actualPart = complexNum.actualPart;
	imaginaryPart = complexNum.imaginaryPart;
	arifmeticOperation = complexNum.arifmeticOperation;
}

void ComplexNumber::setActualPart(double actualPart) {
	this->actualPart = actualPart;
}

void ComplexNumber::setImaginaryPart(double imaginaryPart) {
	this->imaginaryPart = imaginaryPart;
}

void ComplexNumber::setArifmeticOperation(const string& arifmeticOperation) {
	if (checkArifmeticOperation(arifmeticOperation)) {
		this->arifmeticOperation = arifmeticOperation;
	}
	
}

double ComplexNumber::getActualPart() const {
	return actualPart;
}

double ComplexNumber::getImaginaryPart() const {
	return imaginaryPart;
}

string ComplexNumber::getArifmeticOperation() const {
	return arifmeticOperation;
}


bool ComplexNumber::checkArifmeticOperation(const string& s) {
	return (s.compare("+") == 0 || s.compare("-") == 0 || s.compare("*") == 0 ||
		s.compare("/") == 0 || s.compare("R") == 0 || s.compare("I") == 0 ||
		s.compare("=") == 0);
}