
/* 
*	Complex.cpp
*	Created by Chad Lape and 
*
*	This implements the class header of complex
*
*	Saves information within a double of the real and imaginary
*	number constant. This can be derived from the polar form or 
*	copied from cartesian format.
*
*/

#include "Complex.h"
// Handles trig functions for polar complex
#include <math.h>
// For handling string returns
#include <string>
// ostringstream
#include <sstream>
// Handles outputs
#include <iostream>
// Limits the iomanip
#include <iomanip>

// Define Constant PI
const double PI = 3.141592654;

using namespace std;

Complex::Complex(){
	real_constant = 0.0;
	imaginary_constant = 0.0;

}

Complex::Complex(double a, double b){
	real_constant = a;
	imaginary_constant = b;
}

Complex::Complex(double radius, float angle){
	double a;
	double b;

	a = radius*cos((angle*PI)/180.00);
	b = radius*sin((angle*PI)/180.00);

	real_constant = a;
	imaginary_constant = b;
}

// Begin Member Function Definitions

string Complex::String() {
	// Instantiate string stream out
	ostringstream out;
	out << setprecision(2);
	// Add string creating the complex number string format
	out << real_constant << " + " << imaginary_constant << "i";
	// Return the string
	return out.str();
}

// Outputs the Complex Number
void Complex::print() {
	// Prints the string of self
	cout << this->String();
}

// Returns a double representing the radius of a polar equation
// within the complex plane
double Complex::radius() {

	double r = sqrt(pow(this->imaginary_constant, 2) + pow(this->real_constant, 2));
	return r;

}

// Returns a float representing an angle of a polar equation 
// within the complex plane
float Complex::angle() {

	//return result of arc tan (b/a)
	float out = (atan(this->imaginary_constant / this->real_constant));
	out = (out * 180) / PI;
	return out;
}

// Returns the string version of the polar complex 
//for the angle notation
string Complex::string_polar() {
	ostringstream out;
	out << this->radius() << " radius " << this->angle() << " angle";
	return out.str();
}

// Operator Overloads

// Defines the addition of two complex numbers
// which is just their variables changing
void Complex::operator+ (Complex& in) {

	// Add real numbers together
	this->real_constant += in.get_real();
	// Add Imaginary numbers together
	this->imaginary_constant += in.get_imaginary();

}

// Defines the subtraction of two complex Numbers
void Complex::operator- (Complex& in) {

	// Subtract real numbers
	this->real_constant -= in.get_real();
	// Subtract imaginary numbers
	this->imaginary_constant -= in.get_imaginary();

}

// Defines the multiplecation of a scalar to the complex number
void Complex::operator* (double in) {

	this->real_constant *= in;
	this->imaginary_constant *= in;

}

// Defines the Scalar Division of the Complex Number
void Complex::operator/ (double in) {

	this->real_constant = this->real_constant / in;
	this->imaginary_constant = this->imaginary_constant / in;

}

// Defines a way to tell the two are equal to each other
// This is most accurate if private data is in integer format.
// Otherwise there may be discrepencies in function.
bool Complex::operator ==(Complex& in) {



	if (this->get_imaginary() == in.get_imaginary() && this->get_real() == in.get_real()) {
		return true;
	}
	else {
		return false;
	}
	
}