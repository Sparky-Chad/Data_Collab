#pragma once
#ifndef MOVIE_H
#define MOVIE_H

//Imports
#include "Show.h"
#include <string>

using namespace std;

// Class movie which implements show further
class Movie : public Show {
public:
	// Default Constructor
	Movie() : Show()
	{
		rating = 0;
	}
	//Movie calls to constructor of Show and rating
	Movie(double inR, string inT, string inD) : Show(inT, inD)
	{
		rating = inR;
	}

	// Redefine play so it properly lists seperate stuff
	void play();

	//setters and getters
	void setRating(double in) { rating = in; }
	double getRating() { return rating; }

private:
	//five star ranking
	double rating;
};

#endif