// Movies.cpp
// Implementation of Movies
// Chad Lape

#include "Movie.h"
#include <string>
#include <iostream>

using namespace std;


void Movie::play() {
	cout << "Current Rating: " << this->rating << endl;
}
