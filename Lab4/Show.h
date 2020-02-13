#pragma once
#ifndef SHOW_H
#define SHOW_H

#include <string>

using namespace std;

// Defining the show class which can be used as a parent to others

class Show {
public:
	// Constructors
	Show() {
		title = "";
		description = "";
	}
	Show(string inT, string inD) {
		title = inT;
		description = inD;
	}

	// Prints the details of the show
	void print_details();
	// Returns a string of the title and description in print format
	string toString();

	// virtual function play which can be used with other classes
	virtual void play();

	//setters and getters
	string gettitle() { return title; }
	void settitle(string in) { title = in; }

	string getdesc() { return title; }
	void setdesc(string in) { description = in; }
private:
	// Private string data of them
	string title;
	string description;

};


#endif