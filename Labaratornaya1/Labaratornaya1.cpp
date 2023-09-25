//вариант 3
#include <assert.h>
#include "ComplexNumber.h"
#include "Calculator.h"
const string ARIFMETIC_OPERATION_1 = "+";
const string ARIFMETIC_OPERATION_2 = "R";
const string ARIFMETIC_OPERATION_INCORRECT = "%";
const int ACTUAL_PART = 2;
const int IMAGINARY_PART = 1;
const double ACTUAL_PART_2 = 10.3;
const double IMAGINARY_PART_2 = -7.1;
using namespace std;
void printCalc(Calculator &calc ) {
    ComplexNumber* num = calc.getPtr();
    for (int i = calc.getStackSize() - 1; i >= 0; i--)
        cout <<i+1 <<" | " << num[i].getActualPart() << " " << num[i].getImaginaryPart() << " " << num[i].getArifmeticOperation() << endl;
}
int main()
{
    //конструктор инициализации
    ComplexNumber number = ComplexNumber(ACTUAL_PART, IMAGINARY_PART, ARIFMETIC_OPERATION_1); 
    assert(number.getActualPart() == ACTUAL_PART);
    assert(number.getImaginaryPart() == IMAGINARY_PART);
    assert(number.getArifmeticOperation().compare(ARIFMETIC_OPERATION_1)==0) ;

    //конструктор копирования
    ComplexNumber num = number;
    assert(num.getActualPart() == number.getActualPart());
    assert(num.getImaginaryPart() == number.getImaginaryPart());
    assert(num.getArifmeticOperation().compare(number.getArifmeticOperation())==0);

    //методы доступа полей класса
    num.setActualPart(ACTUAL_PART_2);
    num.setImaginaryPart(IMAGINARY_PART_2);
    num.setArifmeticOperation(ARIFMETIC_OPERATION_2);
    assert(num.getActualPart() == ACTUAL_PART_2);
    assert(num.getImaginaryPart() == IMAGINARY_PART_2);
    assert(num.getArifmeticOperation().compare(ARIFMETIC_OPERATION_2)==0);

    //конструктор по умолчанию
    ComplexNumber numTest = ComplexNumber();
    assert(numTest.getActualPart() == 0);
    assert(numTest.getImaginaryPart() == 0);
    assert(numTest.getArifmeticOperation().empty());

    //конструктор инициализации с некоректными данными
    ComplexNumber number1 = ComplexNumber(ACTUAL_PART, IMAGINARY_PART, ARIFMETIC_OPERATION_INCORRECT);
    assert(number1.getArifmeticOperation().empty());
    assert(number1.getActualPart() == 0);
    assert(number1.getImaginaryPart() == 0);
   

    //--------------------------------------------------------------------------------------------------
    Calculator calc,calc3;
    calc.push(number);

    Calculator calc2 = calc;
    assert(calc.equals(calc2));
    calc2.pop();
    assert(calc.equals(calc2)==false);
    assert(calc.getStackSize() == 1);
    calc.push(num);
    assert(calc.getStackSize() == 2);
    ComplexNumber delNum= calc.pop();
    assert(delNum.getActualPart() == num.getActualPart());
    assert(delNum.getImaginaryPart() == num.getImaginaryPart());
    assert(delNum.getArifmeticOperation().compare(num.getArifmeticOperation()) == 0);
    assert(calc.getStackSize() == 1);

    calc.push(num);
    calc.push(number);
    calc.writeInFile("file.txt");
    calc3.getFromFile("file.txt");
    assert(calc.equals(calc3));

    calc.removeAll();
    assert(calc.getStackSize() == 0);

    Calculator calc4;
    calc4.push(number);
    ComplexNumber number2 = ComplexNumber(ACTUAL_PART, IMAGINARY_PART, "=");
    
    calc4.push(number2);
    
    ComplexNumber number4 = calc4.getLastValue();
    assert(number2.getActualPart() == number4.getActualPart());
    assert(number2.getImaginaryPart() == number4.getImaginaryPart());
    assert(number2.getArifmeticOperation().compare(number4.getArifmeticOperation()) == 0);
    ComplexNumber number5 = calc4.getFirstValue();
    assert(number5.getActualPart() == number.getActualPart());
    assert(number5.getImaginaryPart() == number.getImaginaryPart());
    assert(number5.getArifmeticOperation().compare(number.getArifmeticOperation()) == 0);
    ComplexNumber number7 = ComplexNumber(ACTUAL_PART, IMAGINARY_PART, "*");
    calc4.push(number7);
    calc4.push(number7);
    printCalc(calc4);
    cout << "-------------------------------------" << endl;
  
    ComplexNumber number3 = calc4.getAnswer();
    
    cout << number3.getActualPart() << " " << number3.getImaginaryPart() << endl;
    //assert(number3.getActualPart() == 4);
    //assert(number3.getImaginaryPart() == 2);
   
   
    system("pause");
}

