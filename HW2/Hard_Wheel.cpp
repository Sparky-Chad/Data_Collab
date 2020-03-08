// Implements the Hard_Wheel class
// just a basic function which will handle the hard wheel

#include "Hard_Wheel.h"
#include "wheel.h"
#include <iostream>

using namespace std;

bool Hard_Wheel::house_spin(int competing) {
    int svalue = spin();
    cout << "House spins a " << svalue << endl;
    if(svalue >= competing) {
        if(this->current) {
            this->decrease_bounds();
            current = 0;
            return true;
        } else {
            current = 1;
            return true;
        }
    }
    else {
        this->increase_bounds();
        return false;
    }
}

// Handle increase of bounds

void Hard_Wheel::increase_bounds() {
    // Increase the bounds of high by 5
    this->high = high + 5;
    // Increase lower bound by 1
    this->low = low + 1;
    cout << "House increases bounds to [" << low << ", " << high << "]\n";
}

// Handle decrease of bounds

void Hard_Wheel::decrease_bounds() {
    // decrease high by 3
    this->high = this->high - 3;
    // if low will remain higher than the players lower, then lower by a 
    // max of 3, otherwise don't
    if(this->low - 3 > this->min) {
        this-> low = this->low - 3;
    } else if(this->low > this->min) {
        this->low--;
    } else
    {
        this->low = min;
    }
    
    cout << "House decreases bounds to [" << low << ", " << high << "]\n";
}