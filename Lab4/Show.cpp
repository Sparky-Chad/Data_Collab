
// Shows implementation
// Chad Lape

// For strings
#include <string>
// to build strings
#include <sstream>
//Show
#include "Show.h"
// cout 
#include <iostream>

using namespace std;

string Show::toString() {
	ostringstream ss;
	ss << "Title: " << title << endl;
	ss << "Description: " << endl << description << endl;
	return ss.str();
}

void Show::print_details() {
	//Sync and output details through cout stream
	cout.flush();
	cout << this->toString() << endl;
	cout.flush();
}

void Show::play() {
	// Just print details of the show
	cout << "I am a show, play me" << endl;
}
