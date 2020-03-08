#ifndef PLAYER_H_
#define PLAYER_H_

#include "wheel.h"
#include "Hard_Wheel.h"

class Player {

public:

// Constructors
// No Defualt Constructor, must be started with choices
Player(double, bool, int, int);

// Methods
// This is where the player spins and enables the user
// to make a choice to double or halve the bet returns result of the spin
int Player_Spin();

// Handle the house spinning, return amount won
// 0 - halve the bet
// 1 - don't modify the wager
// 2 - double the wager
// (Pass the full bet regardless of if they change it)
int Challenge_House(int bet, int choice);

// Returns current money they have
double current_money() { return Money; }

private: 
int own_spin_value;
double Money;
wheel own_wheel;
wheel* house_wheel;

};



#endif