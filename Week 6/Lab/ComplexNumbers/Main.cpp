/*Author: Zeynep Dogmus
 *Date: March 2013
 *Complex Numbers and Operator Overloading
 */
#include <iostream>
#include "ComplexNumber.h"

using namespace std;

//***********************************
// Operator overloading : <<        *
//***********************************
ostream &operator<<(ostream &output, const ComplexNumber &complex) {
    // If the imaginary part is positive, put a plus before writing
    if (complex.getImaginary() < 0) {
        output << complex.getReal() << complex.getImaginary() << "i";
    }
    else {
        output << complex.getReal() << "+" << complex.getImaginary() << "i";
    }
    return output;
}

//***********************************
// Operator overloading : >>        *
//***********************************
istream &operator>>(istream &input, ComplexNumber &complex) {
    double real, imaginary;

    input >> real;
    input >> imaginary;
    complex.setReal(real);
    complex.setImaginary(imaginary);

    return input;
}

//******************************************************************
// Add num1 and num2, return the result as a new complex number    *
// This function uses get and set functions of ComplexNumber class *
//******************************************************************
ComplexNumber operator+(const ComplexNumber &num1, const ComplexNumber &num2) {
    ComplexNumber result;
    double realResult, imaginaryResult;

    realResult = num1.getReal() + num2.getReal();
    imaginaryResult = num1.getImaginary() + num2.getImaginary();

    result.setReal(realResult);
    result.setImaginary(imaginaryResult);

    return result;
}

//*******************************************************************
// This is a friend function declared by ComplexNumber class.      *
// Therefore, it is able to access non-public members of this class.*
// This function adds rhs to lhs and returns lhs                     *
//*******************************************************************
const ComplexNumber &operator+=(ComplexNumber &lhs, const ComplexNumber &rhs) {
    *(lhs.real) = *(lhs.real) + *(rhs.real);
    *(lhs.imaginary) = *(lhs.imaginary) + *(rhs.imaginary);
    return lhs;
}

int main() {
    ComplexNumber c1, c2;
    ComplexNumber sumResult, mulResult;

    cout << "Enter two complex numbers; first real part, then imaginary part(without i)" << endl;
    cin >> c1 >> c2;

    cout << endl;
    cout << "First complex number: " << c1 << endl;
    cout << "Second complex number: " << c2 << endl << endl;

    sumResult = c1 + c2;
    cout << "first + second" << endl;
    cout << "result : " << sumResult << endl << endl;

    c1 -= c2;
    cout << "first -= second" << endl;
    cout << "First complex number: " << c1 << endl;
    cout << "Second complex number: " << c2 << endl << endl;

    mulResult = c1 * c2;
    cout << "first * second" << endl;
    cout << "result : " << mulResult << endl << endl;

    c2 += c1 += c2;
    cout << "second += first += second" << endl;
    cout << "First complex number: " << c1 << endl;
    cout << "Second complex number: " << c2 << endl << endl;

    return 0;
}
