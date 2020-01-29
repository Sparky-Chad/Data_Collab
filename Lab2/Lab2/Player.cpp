#include <iostream>
#include <iomanip>
#include <string>
#include "Player.h"
#include <cstdlib>

using namespace std;




Player::Player(string name) {
	this->name = name;
	int temp;

	temp = (int)(rand() % 20 + 50);
	this->shotsTaken = temp;
	this->shotsMade = (rand() % temp);

	temp = (int)(rand() % 40 + 70);
	this->passesAttempted = temp;
	this->passesMade = (int)(rand() % temp);
}

/*Player::Player(string s, double shotstak, double shotsmade, double passat, double passesmade) {
	name = s;
	shotsTaken = shotstak;
	shotsMade = shotsmade;
	passesAttempted = passat;
	passesMade = passesmade;
}*/

void Player::setName(string x) {
	name = x;

}


int Player::getshotsTaken() {
		return shotsTaken;
}

void Player::setshotsTaken(int x) {
	shotsTaken = x;
}


int Player::getshotsMade() {
		return shotsMade;
}

void Player::setshotsMade(int x) {
	shotsMade = x;
}


int Player::getpassesAttempted() {
	return passesAttempted;
}

void Player::setpassesAttempted(int x) {
	passesAttempted = x;
}

int Player::getpassesMade() {
	return passesMade;
}

void Player::setpassesMade(int x) {
	passesMade = x;
}

bool Player::passBall() {
	bool outcome = 1;
	double passPercentage;
	if (passesAttempted >= 10) {
		passPercentage = (passesMade / passesAttempted) * 100;
	}else{
		passPercentage = 80;
	};

	int prob = rand() % 100 +1;
	double probability = static_cast<double>(prob);

	if (probability > passPercentage) {
		outcome = 0;
		passesAttempted = passesAttempted + 1;
	}
	else
	{
		passesAttempted = passesAttempted + 1;
		passesMade = passesMade + 1;
	};
	return outcome;
}

int Player::takeShot(int possiblePts) {
	double shooterPercentage;
	int prob;
	double probability;

	if (shotsTaken != 0) {
		shooterPercentage = (shotsMade / shotsTaken) * 100;
	}
	else {
		shooterPercentage = 80;
	};

	if (possiblePts == 1) {
		prob = rand() % 80 + 1;
	} else if (possiblePts == 2) {
		prob = rand() % 100 + 1;
	} else if (possiblePts == 3) {
		prob = rand() % 120 + 1;
	};
	probability = static_cast<double>(prob);

	shotsTaken = shotsTaken + 1;

	if (probability < shooterPercentage) {
		shotsMade = shotsMade + 1;
		return possiblePts;
	}
	
	return 0;
}








void Player::getStats() {
	cout << "Stats for " << name << ":" << endl;
	cout << endl;
	cout << "Shots Taken: " << shotsTaken<< endl;
	cout << "Shots Made: " << shotsMade << endl;
	cout << "Passes Attempted: " << passesAttempted << endl;
	cout << "Passes Made: " << passesMade << endl;
	cout << endl;
	cout << endl;
}
