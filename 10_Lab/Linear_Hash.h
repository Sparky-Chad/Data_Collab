#ifndef LINEAR_HASH_H
#define LINEAR_HASH_H

// Must include string 
#include <string>
// Including output streams for print output
#include <iostream>

#define HASH_TABLE_SIZE 500


// Macro which creates the backend for the counter system
// and defines a macro to either meaningless nothing or to
// extending the count when searching a spot
//
// This compile time attribute would mean that you would want
// the header file to only be linked while compiled to ensure
// the macros work properly
#ifdef COUNTER
    extern int searchspot;
    // Macro search count which will then iterate the searchspot int
    #define SEARCHCOUNT searchspot++;

#else
    // If not going to be a counting thing then define
    // the macro keyword of searchcount to nothing
    #define SEARCHCOUNT

#endif
using namespace std;

template <class T>
class Linear_Hash
{
public:
    Linear_Hash();
    ~Linear_Hash();

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

    // Returns the length
    int getLength() { return length; }
    // Will print out, the entire list to the user
    void print();


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
    T** list;

};

#endif


template <class T>
// Create the defined template metheds
Linear_Hash<T>::Linear_Hash()
{
    list = new T*[HASH_TABLE_SIZE];
    length = 0;
    
    // Fill the list with empty nullptr values
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        list[i] = nullptr;
    }
}

// Define the constructor to delete any non null memory
// If there begins to have memory links within this check for
// if there are miscelaneous memory locations being accessed
//
// A quick fix might be to check if list[i] < 0x5000
// As it seems heap will always be above this value
template <class T>
Linear_Hash<T>::~Linear_Hash()
{
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if(list[i] != nullptr && ((void *)list[i]) > (void*)0x500)
        {
            delete list[i];
        }
    }
    delete[] list;
}


// The insert function takes in the value the user wants to input
// then the code will take that and create a hash value 
// using modulus and return the number of iterations
// it must linearly probe the hash function
template <class T>
void Linear_Hash<T>::insert(T* nnode)
{

    // create new pointer value to the given in value
    T in = *nnode;

    // Now send the new node to create a hash
    int hash = this->hash(in);

    while(this->list[hash] != nullptr)
    {
        // Add one onto the hash to do a linear probe
        hash++;
        SEARCHCOUNT
    }

    // Insert the item into that location
    this->list[hash] = nnode;
    length++;
}

// The find function will continue until it has either reached the end of the array
// or it has found the item that it wishes to find. This will then output beack that
// same item or return a nullptr

// TODO:    Look into changing the system to an exponential type of hash or rehashing it till a new 
//          value can be found by the system so that there is not a need to move the values around too much
template <class T>
T* Linear_Hash<T>::getItem(T* input)
{
    if(this->length == 0) return nullptr;
    T in = *input;
    // create the hash to act as the index
    int hash = this->hash(in);

    // Check first for the nullptr to protect the program from a potential crash
    while (list[hash] != nullptr)
    {
        SEARCHCOUNT
        if(in == *list[hash])
        {
            // if the correct thing is found then return that value
            return list[hash];

        }

        // iterate the hash value
        hash++;
        
    }

    // If the correct value is not found then just return a nullptr
    return nullptr;
}

/*  The remove function will act nearly identical to the previous one but will then 
    check to move back the rest of the values so that they are not affected by the 
    removal of this node, this would be due to the linear nature of it. The removal 
    function will travel to the end of the current hash line. But this could result in
    under or overwriting of data which may cause some potential issues          */

    // Returns the value not the pointer of the object
template <class T>
T* Linear_Hash<T>::removeItem(T* input)
{
    if(this->length == 0) return nullptr;
    T in = *input;
    // Create a starting hash of the value
    int hash = this->hash(in);
    T* out;
    int index = 0;
    while (this->list[hash] != nullptr)
    {
        SEARCHCOUNT
        if (*this->list[hash] == in)
        {
            out = this->list[hash];
            this->list[hash] = nullptr;
        }
        index++;
    }
    // If the end of a line has been reached then the program was unable to 
    // find the inputed value so throw an exception of that
    if(this->list[hash] == nullptr)
    {
        return nullptr;
    }

    // Now the function will search down the current line of indexes
    // and move them back by one so that they remain in a linear line

    while (this->list[hash + 1] != nullptr && hash + 1 != HASH_TABLE_SIZE)
    {
        // First to check and make sure this line of hashes are proper
        // if not the case then the current hash value is going to be invalid
        // and must be switched to a nullptr
        if((this->hash(*this->list[hash+1]) + index + 1 > hash)) break;


        // Perform a swap so that the new value is nullptr
        this->list[hash] = this->list[hash+1];
        hash++;
        this->list[hash] = nullptr;
    }

    length--;

    // After all of the operations are completed then return the value of the system
    return out;
}

/*
    The print function will return a output which is going to be 10x10
    values and will then have all of the needed things
*/
template <class T>
void Linear_Hash<T>::print()
{

    // Print out the whole array with the hash value next to each item and the index at the front
    for(int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        cout << to_string(i) << ": ";
        if(this->list[i] == nullptr)
        {
            cout << "****" << endl;
        }
        else
        {
            cout << *this->list[i] << " | " << this->hash(*this->list[i]) << endl;
        }
    }
}

/*
    This is the hashing function which all it will do now is just grab the
    modulus of the number when compared to the length
*/
template <class T>
int Linear_Hash<T>::hash(string in)
{
    int out = 0;
    for(int i = 0; i < in.size(); i++)
    {
        out += (int)(in[i]);
    }
    return out % HASH_TABLE_SIZE;
}