#pragma once
#ifndef COMPLEX_H
#define COMPLEX_H

/*
	Complex.h
	Created by: Chad Lape and Colton Murray
*/

// For a return of string value
#include <string>
// Use of math library for trig
#include <math.h>

using namespace std;


class Complex {
public:
	// Default Constructor
	Complex();
	// Cartesian Form Constructor
	Complex(double, double);
	// Polar Form Constructor
	Complex(double, float);
	
	
	//Getters/Setters
	
	// constant setter and getter
	void set_real(double in) { 
		real_constant = in; 	}
	double get_real() { 
		return real_constant; 
	}
	// imaginary setter and getter
	void set_imaginary(int in) {
		imaginary_constant = in;
	}
	double get_imaginary() {
		return imaginary_constant;
	}

	// Returns a string version of the information
	string String();
	// Prints the complex number using the String function
	void print();

	// Polar Member Functions
	// Returns radius in polar complex
	double radius();
	// Returns the angle in polar complex
	float angle();
	// Returns a string version of the polar version
	string string_polar();

	// Overload Operators

	// Adds together the constants
	void operator +(Complex&);
	// Subtracts the constants
	void operator -(Complex&);
	// Multiplys the constants and deals with weirdness
	void operator *(double);
	// Divides and deals with weirdness
	void operator /(double);

	// Returns bool for if the two are the same
	bool operator ==(Complex&);



private:
	// This assuming complex form as a + bi
	// real constant a
	double real_constant;
	//imaginary constant b
	double imaginary_constant;

	// This had originally been an int but ran into the problem 
	// that too much information was lost when done this way.
};


#endif