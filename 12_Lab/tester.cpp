#include <iostream>
#include "algorithms.h"

#include <string>
#include <random>
#include <ctime>

#define MY_SIZE 25

using namespace std;



int* arr = new int[MY_SIZE];


int main()
{
    srand(time(nullptr));

    cout << "pre_go = [";

    int random = rand() % 1000;
    arr[0] = random;
    cout << random;

    for(int i = 1; i < MY_SIZE; i++)
    {
        random = rand() % 1000;
        arr[i] = random;
        cout << ", " << arr[i];
    }
    cout << "]\n\n";

    //algorithms::radix(arr, MY_SIZE);

    algorithms::counting(arr, MY_SIZE);
    cout << "\nfinal arr = [";
    cout << arr[0];
    for(int i = 1; i < MY_SIZE; i++)
    {
        cout << ", " << arr[i];
    }
    cout << "]\n\n";
    return 0;
}