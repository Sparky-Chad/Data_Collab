// This will be testing the counter class

// Use the pre defined created sytem which checks the
// differnet stuff 

// Defines systems for the others to be able to create
// their counters when being tested
#include "counter.h"

//#include "hash_2d.h"
#include "BinaryTree.h"
#include <iostream>

#include <stdlib.h>
#include <ctime>


#include <string>

#include "Linear_Hash.h"

using namespace std;
#define arr_size 100

// Get the ints from counter.h to use in this function
extern int searchspot;  // 1D Hash counter
extern int hashspot;    // 2D Hash Counter
extern int binaryspot;  // Binary Tree Counter

int values[100] = { 0 };

void populateArray() {

    for (int i = 0; i < 100; i++) {
        values[i] = 1 + rand() % 500;
    }
}




int main()
{
    BinaryTree<int> testTree;
    Linear_Hash testHash;
    int checkSum = 0;
    int foundVals[100] = { 0 };
    int foundValsTree[100] = { 0 };


    //BinaryTree testBinaryTree;
    for (int i = 0; i < 99; ++i) {

        populateArray(); // populate the vector with random numbers
    }

    for (int i = 0; i < 49; ++i) {

        testHash.insert(values[i]);
        testTree.insert(values[i]);

    }

    cout << "HASH->Spots checked for inserting first 50:" << searchspot << endl;
    cout << "TREE->Spots checked for inserting first 50:" << binaryspot << endl;


    for (int i = 0; i < 49; ++i) {

        if ((values[i] % 7) == 0) {
            testHash.remove(values[i]);
            testTree.remove(values[i]);
        };


    }
    cout << "HASH->Spots checked for removing (% 7):" << searchspot << endl;
    cout << "TREE->Spots checked for removing (% 7):" << binaryspot << endl;


    for (int i = 50; i < 99; ++i) {

        testHash.insert(values[i]);
        testTree.insert(values[i]);


    }

    for (int i = 50; i < 99; ++i) {
        testHash.remove(values[i]);
        testTree.remove(values[i]);

    }

    cout << "HASH->Spots checked for removing second 50:" << searchspot << endl;
    cout << "TREE->Spots checked for removing second 50:" << binaryspot << endl;




    cout << "Found Values: ";
    for (int i = 0; i < 99; ++i) {

        if ((values[i] % 9) == 0) {
            foundVals[i] = testHash.find(values[i]);
            if (testTree.find(values[i]) == nullptr){
                foundValsTree[i] = 0;
            }
            else {
                foundValsTree[i] = binaryspot;
            }
        }
        
        cout <<values[i]<<": "<< "Hash- " << foundVals[i] << "|" << " Tree- " << foundValsTree[i] << endl;
        binaryspot = 0;
    }
    cout << endl;

   
    cout <<testHash.find(9)<< endl;
    testHash.print();
    
    return 0;
}