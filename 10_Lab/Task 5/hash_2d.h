#ifndef HASH_2D
#define HASH_2D

#include <iostream>
#include <string>

#include "LinkedList.h"

// Set up counter macros
#ifdef COUNTER
extern int hashspot;
#define HASH_COUNT hashspot++;
#else
#define HASH_COUNT
#endif

#define Max_Size 500

using namespace std;

/*
    This class will use a linked list to define a 2D 
    Hash Table which is able to handle any problems due to
    hash collisions automatically
*/

template <class T>
class Hash_2D
{
public:
    Hash_2D();
    ~Hash_2D();

    // The insert function will return the number of spots that it attempts to check before being able
    // to place the inserted item into its place in the array. This will give an indication to the user
    // whether or not this is a cheap operation and they may wish this data to be outputted.
    void insert(T*);

    // The find function will return the given object that it had been directed to move too
    T* getItem(T*);

    // The Remove function will return the given value to find and then remove the value from the
    // hash table, while doing this it should also probably also move back any of the other things
    // as to keep everything in line
    T* removeItem(T*);

    // Will print out, the entire list to the user
    void print();

    int getLength() { return length; }


    // Exception class for if the insert function finds the value already located within the array
    class ItemExistsException
    { public: string print() { return "Given item exsists already\n"; } };
    
    // Item to be removed was not found
    class ItemNotFoundException
    { public: string print() {return "Given item was not found\n"; } };

    // Exception for if an item does not fit due to the fact that there is not enough space
    class HashTableOutOfBounds
    { public: string print() {return "Hash table is out of bounds\n"; } };
private:

    int hash(string);

    // Private data of the class
    // The size of the linear hash
    int length;
    // Set up a dynamic array length to serve as the possible system to do it
    LinkedList<T>** list;

};


#endif

// Should be defined within the header file so that the c macros will work
// properly during compile time


// Default constructor which constructs the empty hash object
template <class T>
Hash_2D<T>::Hash_2D()
{
    length = 0;
    list = new LinkedList<T>*[Max_Size];

    for(int i = 0; i < Max_Size; i++)
    {
        list[i] = nullptr;
    }
}

// Descrtuctor
template <class T>
Hash_2D<T>::~Hash_2D()
{
    for(int i = 0; i < Max_Size; i++)
    {
        if(list[i] != nullptr && ((void*)list[i]) > (void*)0x500)
        {
            delete list[i];
            list[i] = nullptr;
        }
    }
    delete[] list;
}

/*
    Insert Function will take the given value into the hash
    and if it matches an item alreeady in there will then add
    the new item to the end of the list of those hashes with 
    the same value
*/
template <class T>
void Hash_2D<T>::insert(T* in)
{
    int hash = this->hash(*in);
    // Traverse to the correct location
    // if there is already a value there then throw
    // an exception if it is the same data point
    if(list[hash] == nullptr)
    {
        list[hash] = new LinkedList<T>();
        list[hash]->addItem(in);
    }
    else
    {
        list[hash]->addItem(in);
    }
    length++;
}


/*
    The find function will follow the given list untill
    it reaches the end or it can find the value which it was
    wanting to find
*/
template <class T>
T* Hash_2D<T>::getItem(T* in)
{
    // Create the hash to then find the index to search
    int hash = this->hash(*in);

    T* out = this->list[hash]->getItem(in);
    this->list[hash]->addItem(in);
    return out;
}


// Create a remove function which will throw an exception
// if it can't find the given value
template <class T>
T* Hash_2D<T>::removeItem(T* in)
{
    // Create the hash to then find the index to search
    int hash = this->hash(*in);

    if(this->list[hash] == nullptr) return nullptr;
    // Return the item from the list
    try
    {
        T* out = this->list[hash]->getItem(in);
        if(this->list[hash]->Size() == 0)
        {
            delete this->list[hash];
            this->list[hash] = nullptr;
        }
        if(out == nullptr) return nullptr;
        length--;
        return out;

    }
    catch(typename LinkedList<T>::ListIsEmpty e)
    {
        return nullptr;
    }
    
}

/*
    The print function will return each item and if it
    contains a list of them then the whole list as well, 
    with the hashes put at the front
*/
template <class T>
void Hash_2D<T>::print()
{
    for(int i = 0; i < Max_Size; i++)
    {
        cout << i << ": ";
        if(this->list[i] == nullptr)
        {
            cout << "****" << endl;
        }
        else
        {
            T* temp = list[i].seeAt(0);
            cout << this->hash(*temp->data) << " | " << *temp->data;
            while(temp->next != nullptr)
            {
                cout << " --> " << *temp->next->data;
                temp = list[i].seeNext();
                if(temp == nullptr) break;
            }
            cout << endl;
        }
    }
}

/*
    Simple hash which will use the modulus function
    to create the hashes in a simple manner
*/
template <class T>
int Hash_2D<T>::hash(string in)
{
    int out = 0;
    for(int i = 0; i < in.size(); i++)
    {
        out += (int)(in[i]);
    }
    return out % Max_Size;
}