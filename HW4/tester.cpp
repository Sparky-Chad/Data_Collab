// This will be testing the counter class

#include "hash_2d.h"
#include <iostream>

#include <string>

using namespace std;

#define arr_size 12
int main()
{
    Hash_2D hasher;

    // Create a set which will be inputed into the program

    int arty[] = {300, 800, 1300, 900, 200, 255, 15, 12, 5, 60000, 53, 78}; 

    // loop through the set and put all values in there
    for(int i = 0; i < arr_size; i++)
    {
        hasher.insert(arty[i]);
    }

    hasher.print();
}