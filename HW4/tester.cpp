// This will be testing the counter class

// Use the pre defined created sytem which checks the
// differnet stuff 

// Defines systems for the others to be able to create
// their counters when being tested
#include "counter.h"
#include "Linear_Hash.h"
#include "hash_2d.h"
#include "BinaryTree.h"
#include <iostream>

#include <stdlib.h>
#include <ctime>

#include <string>

using namespace std;
#define arr_size 100

// Get the ints from counter.h to use in this function
extern int searchspot;  // 1D Hash counter
extern int hashspot;    // 2D Hash Counter
extern int binaryspot;  // Binary Tree Counter
int main()
{
    srand(time(nullptr));
}