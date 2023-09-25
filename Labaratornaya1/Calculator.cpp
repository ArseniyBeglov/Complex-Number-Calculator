#include "Calculator.h"
#include <iomanip>
#include<fstream>

Calculator::Calculator() {
	count=0;
	allocated = 0;
	stackPtr = new ComplexNumber[count];
}

Calculator::Calculator(const Calculator& otherStack) {
	count = otherStack.getStackSize();
	stackPtr = new ComplexNumber[count];
	for (int i = 0; i < count; i++)
		stackPtr[i] = otherStack.stackPtr[i];
}

Calculator::~Calculator() {
	removeAll();
}

void Calculator::push(const ComplexNumber& value){	
	if (count >= allocated) {
		grow();
	}
	stackPtr[count++] = value;
}

ComplexNumber Calculator::pop() {
	ComplexNumber num = stackPtr[count-1];
	if (count > 0) {
		stackPtr[--count];
	}
	return num;
}

int Calculator::getStackSize() const{
	return count;
}

ComplexNumber* Calculator::getPtr() const{
	return stackPtr;
}

void Calculator::grow() {
	ComplexNumber* tmp = new ComplexNumber[count + 1];
	for (auto i = 0; i < count; i++)
		tmp[i] = stackPtr[i];
	delete[] stackPtr;
	stackPtr = tmp;
	allocated += 1;
}

ComplexNumber Calculator::getLastValue() const {
	return stackPtr[count-1];
}

ComplexNumber Calculator::getFirstValue() const{
	return stackPtr[0];
}

void Calculator::removeAll() {
	if (allocated) {
		int size = count;
		for (int i = 0; i < size; i++) {
			pop();
		}
	}
	count = 0;
}

bool Calculator::equals(const Calculator& obj) const{
	if (obj.count != this->count) {
		return false;
	}
	else {
		for (int i = 0; i < obj.count; i++) {
			ComplexNumber num1 = obj.stackPtr[i];
			ComplexNumber num2 = this->stackPtr[i];
			if (!(num1.getActualPart() == num2.getActualPart() && num1.getImaginaryPart() == num2.getImaginaryPart()
				&& num1.getArifmeticOperation().compare(num2.getArifmeticOperation()) == 0)) {
				return false;
			}
		}
	}
	return true;
}

void Calculator::writeInFile(const string& path) {
	ofstream fout;
	fout.open(path);
	for (int i = 0; i < count; i++) {
		fout << stackPtr[i].getActualPart() << endl << stackPtr[i].getImaginaryPart() << endl <<
			stackPtr[i].getArifmeticOperation() ;
		if (i != count - 1) {
			fout << endl;
		}
	}
}

void Calculator::getFromFile(const string& path) {
	ifstream fin;
	fin.open(path);
	while (!fin.eof()) {
		double actPart;
		double imgPart;
		string operation;
		fin >> actPart >> imgPart >> operation;
		ComplexNumber num = ComplexNumber(actPart, imgPart, operation);
		push(num);
	}
}

ComplexNumber Calculator::plus(const ComplexNumber& num1, const ComplexNumber& num2) {
	ComplexNumber ans = ComplexNumber(num1.getActualPart() + num2.getActualPart(),
		num1.getImaginaryPart() + num2.getImaginaryPart(),
		num2.getArifmeticOperation());
		return ans;
}

ComplexNumber Calculator::minus(const ComplexNumber& num1, const ComplexNumber& num2) {
	ComplexNumber ans = ComplexNumber(num1.getActualPart() - num2.getActualPart(),
		num1.getImaginaryPart() - num2.getImaginaryPart(),
		num2.getArifmeticOperation());
	return ans;
}

ComplexNumber Calculator::multiply(const ComplexNumber& num1, const ComplexNumber& num2) {
	ComplexNumber ans = ComplexNumber(num1.getActualPart()*num2.getActualPart() 
		- num1.getImaginaryPart()*num2.getImaginaryPart(), 
		num1.getActualPart() * num2.getImaginaryPart() + num2.getActualPart() * num1.getImaginaryPart(),
		num2.getArifmeticOperation());
	return ans;
}

ComplexNumber Calculator::division(const ComplexNumber& num1, const ComplexNumber& num2) {
	double del = num2.getActualPart() * num2.getActualPart() + num2.getImaginaryPart() * num2.getImaginaryPart();
	ComplexNumber ans = ComplexNumber((num1.getActualPart() * num2.getActualPart()
		+ num1.getImaginaryPart() * num2.getImaginaryPart())/del,
		(num2.getActualPart() * num1.getImaginaryPart() - num1.getActualPart() * num2.getImaginaryPart())/del,
		num2.getArifmeticOperation());
	return ans;
}

ComplexNumber Calculator::getAnswer() {
	bool flag = false;
	for (int i = 0; i < count; i++) {
		if (stackPtr[i].getArifmeticOperation().compare("=") == 0) {
			flag = true;
		}
	}
	ComplexNumber* newstackPtr = new ComplexNumber[count];
	if (flag) {
		int j = 0;
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i].getArifmeticOperation()) == 2) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i].getArifmeticOperation()) == 1) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count; i++) {
			if (priority(stackPtr[i].getArifmeticOperation()) == 3) {
				newstackPtr[j++] = stackPtr[i];
			}
		}
		for (int i = 0; i < count ; i++) {
			if (newstackPtr[i].getArifmeticOperation().compare("*") == 0) {
				newstackPtr[i+1] = multiply(newstackPtr[i], newstackPtr[i + 1]);
			} 
			else if (newstackPtr[i].getArifmeticOperation().compare("/") == 0 ) {
				newstackPtr[i + 1] = division(newstackPtr[i], newstackPtr[i + 1]);
			} 
			else if (newstackPtr[i].getArifmeticOperation().compare("+") == 0 ) {
				newstackPtr[i + 1] = plus(newstackPtr[i], newstackPtr[i + 1]);
			}
			else if (newstackPtr[i].getArifmeticOperation().compare("-") == 0) {
				newstackPtr[i + 1] = minus(newstackPtr[i], newstackPtr[i + 1]);
			}
		}
		
		
		for (int i = j -1; i >= 0; i--)
			cout << i + 1 << " | " << newstackPtr[i].getActualPart() << " " << newstackPtr[i].getImaginaryPart() << " " << newstackPtr[i].getArifmeticOperation() << endl;
	}
	return  newstackPtr[count - 1];
}

int Calculator::priority(const string& s) {
	if (s.compare("+") == 0 || s.compare("-") == 0) {
		return 1;
	}
	if (s.compare("*") == 0 || s.compare("/") == 0) {
		return 2;
	}
	if (s.compare("=") == 0) {
		return 3;
	}
}