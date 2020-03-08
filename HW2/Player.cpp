// Implements the player class

#include "Player.h"
#include "wheel.h"
#include "Hard_Wheel.h"

using namespace std;

Player::Player(double money_in, bool hard_mode, int lower_bound, int upper_bound) {
    this->Money = money_in;
    own_wheel = wheel(lower_bound, upper_bound);
    if(hard_mode) {
        // If hard mode, point to a new hard wheel which will handle the special cases
        // of hard wheel on its own.
        this->house_wheel = new Hard_Wheel(&own_wheel);
    }
    else {
        this->house_wheel = new wheel(lower_bound, upper_bound);
    }
}

int Player::Player_Spin() {

    own_spin_value = own_wheel.spin();
    return own_spin_value;

}


int Player::Challenge_House(int bet, int choice) {

    // Handle money changing

    switch(choice) {

        case 0: 
        // Halved bet and so house must win both spins
        if(house_wheel->house_spin(own_spin_value)) {
            if(house_wheel->house_spin(own_spin_value)) {
                // Bet is even and there is no change in value
                Money -= bet;
                return (-1 * bet);   
            }
        }
        // If either failed no change in the bet
        return 0;
        break;

        case 2:
        // Double bet, the handle 2 spins
        if(!house_wheel->house_spin(own_spin_value)) {
            // player won
            if(!house_wheel->house_spin(own_spin_value)) {
                // Player won both rounds
                Money += 2*bet;
                return (2 * bet);
            }
        }
        // House won any of them
        Money -= 2*bet;
        return (-2 * bet);
        break;
        
        case 1:
        default:
        // Normal bet handling, one spin
        if(house_wheel->house_spin(own_spin_value)) {
            Money -= bet;
            return (-1*bet);
        }
        Money += bet;
        return bet;
        break;
    }

}