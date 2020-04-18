// Just for testing the hashes nice and quickly

#include <iostream>
#include <string>
#include <sstream>


#include "hash_2d.h"

using namespace std;

#define arrsize 12

int main()
{
    string o = "hello there my name is jeff i have no idea who me";
    string arr[arrsize];

    stringstream ss(o);

    int i = 0;
    while (ss.good() && i < arrsize)
    {
        ss >> arr[i];
        i++;
    }

    // Create hash table to use
    Hash_2D<string> hash;
    for(i = 0; i < arrsize; i++)
    {
        hash.insert(new string(arr[i]));
    }

    hash.print();
}