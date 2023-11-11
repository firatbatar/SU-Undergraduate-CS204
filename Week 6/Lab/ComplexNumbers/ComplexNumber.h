/*Author: Zeynep Dogmus
 *Date: April 2013
 *Complex Numbers and Operator Overloading
*/
#ifndef COMPLEXNUMBER_H_
#define COMPLEXNUMBER_H_
#include<iostream>

using namespace std;

class ComplexNumber
{
public:
	ComplexNumber();
	~ComplexNumber();
	ComplexNumber(const ComplexNumber &);
	const ComplexNumber& operator=(const ComplexNumber &);
	const ComplexNumber& operator-=(ComplexNumber &);
	ComplexNumber operator*(const ComplexNumber &);
	void setReal(double);
	void setImaginary(double);
	double getReal() const;
	double getImaginary() const;

	friend const ComplexNumber& operator+=(ComplexNumber &,const ComplexNumber &);

private:
	double *real;
	double *imaginary;
};

#endif /* COMPLEXNUMBER_H_ */
