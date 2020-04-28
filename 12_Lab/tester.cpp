#include <iostream>
#include "algorithms.h"
#include "student.h"
#include "Student_LinkedList.h"

#include <string>
#include <random>
#include <ctime>

#define MY_SIZE 25

using namespace std;

template <class T>
using algType = void (*)(T*, int);


/*
class somethng_base
{
public:
    int data;
    somethng_base() { this->data = 0;}
    somethng_base(int in) {this->data = in;}

    ~somethng_base() {}
    virtual bool operator >(somethng_base&) {return false;}
    virtual bool operator <(somethng_base&) {return false;}
    virtual bool operator ==(somethng_base&) {return false;}
    virtual somethng_base& operator =(int& in) {this->data = in;}
    virtual operator int() {return this->data; }

    friend std::ostream& operator<<(std::ostream& out, const somethng_base& in);
};

class derive: public somethng_base
{
public:
    derive() : somethng_base{} {}
    derive(int in) : somethng_base{in} {}
    ~derive() {}
    bool operator >(somethng_base& o) { return this->data > o.data;}
    bool operator <(somethng_base& o) { return this->data < o.data; }
    bool operator ==(somethng_base& o) {return this->data == o.data; }

    somethng_base& operator=(int& in) { this->data = in; return *this;}
    virtual operator int() { return this->data; }

    friend std::ostream& operator<<(std::ostream& out, const somethng_base& in);
};

std::ostream& operator<<(std::ostream& out, const somethng_base& in)
{ out << in.data; return out; }
*/

student_base* arr;

int main()
{
    srand(time(nullptr));

    cout << "pre_go = [";


    wordy_random first("/home/lapech/Programming/Working_Classes/Data_Collab/first-names.txt");
    wordy_random last("/home/lapech/Programming/Working_Classes/Data_Collab/names.txt");

    arr = new student_fname[MY_SIZE];
    int random;
    for(int i = 1; i < MY_SIZE; i++)
    {
        random = rand() % 100000;
        string rfirst = first.getrandom();
        string rlast = last.getrandom();

        arr[i] = student_fname(random, rfirst, rlast);

        cout << random << "|" << rfirst << "|" << rlast << " ---- ";
        
    }
    cout << "]\n\n";

    //algorithms::radix(arr, MY_SIZE);
    algType<student_base> counter = algorithms::radix<student_base>;
    
    //algorithms::counting(arr, MY_SIZE);
    
    counter(arr, MY_SIZE);
    
    cout << "\nfinal arr = [";
    cout << arr[0];
    for(int i = 1; i < MY_SIZE; i++)
    {
        cout << ", " << arr[i];
    }
    cout << "]\n\n";
    return 0;
}