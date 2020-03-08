#ifndef WHEEL_H_
#define WHEEL_H_

#include "wheel.h"


// Extends functionality of regular wheel class
class Hard_Wheel : public wheel {

public:
    Hard_Wheel() : wheel() 
    { current = 0; }

    Hard_Wheel(wheel *in) : wheel(in->get_low(), in->get_high())
    {
        // 
        min = in->get_low();
    }

    // virtual function of the house spin
    bool house_spin(int competing);

private:
// Since last win, counter for how long its been since house win
bool current;
// The minimum bound it can be
int min;
// Increase bounds
void increase_bounds();
// decrease bounds
void decrease_bounds();

};

#endif