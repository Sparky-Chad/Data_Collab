#ifndef HASH_2D
#define HASH_2D

#include <iostream>
#include <string>

// Set up counter macros
#ifdef COUNTER
extern int shashspot;
hashspot = 0;
#define HASH_COUNT hashspot++;
#else
#define HASH_COUNT
#endif

#define Max_Size 500

using namespace std;
// struct for the linked list
struct node
{
    int data;
    node* next = nullptr;
    node* prev = nullptr;
};

/*
    This class will use a linked list to define a 2D 
    Hash Table which is able to handle any problems due to
    hash collisions automatically
*/

class Hash_2D
{
public:
    Hash_2D();
    ~Hash_2D();

    // The insert function will return the number of spots that it attempts to check before being able
    // to place the inserted item into its place in the array. This will give an indication to the user
    // whether or not this is a cheap operation and they may wish this data to be outputted.
    int insert(int);

    // The find function will return the given object that it had been directed to move too
    node* find(int);

    // The Remove function will return the given value to find and then remove the value from the
    // hash table, while doing this it should also probably also move back any of the other things
    // as to keep everything in line
    int remove(int);

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

    int hash(int);

    // Private data of the class
    // The size of the linear hash
    int length;
    // Set up a dynamic array length to serve as the possible system to do it
    node** list;

};


#endif

// Should be defined within the header file so that the c macros will work
// properly during compile time


// Default constructor which constructs the empty hash object
Hash_2D::Hash_2D()
{
    length = 0;
    list = new node*[Max_Size];

    for(int i = 0; i < Max_Size; i++)
    {
        list[i] = nullptr;
    }
}

// Descrtuctor

Hash_2D::~Hash_2D()
{
    for(int i = 0; i < Max_Size; i++)
    {
        if(list[i] != nullptr && ((void*)list[i]) > (void*)0x500)
        {
            // Now make sure each node of the object is removed
            node* temp = list[i]->next;
            list[i]->next = nullptr;
            while (temp != nullptr)
            {
                temp->prev = nullptr;
                node* next = temp->next;
                temp->next = nullptr;
                delete temp;
                temp = next;
            }
            if(list[i] != nullptr) delete list[i];
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
int Hash_2D::insert(int in)
{
    // new pointer to the node
    node* nnode = new node {in};

    int hash = this->hash(in);

    int out = 0;

    // Traverse to the correct location
    // if there is already a value there then throw
    // an exception if it is the same data point
    if(list[hash] == nullptr)
    {
        list[hash] = nnode;
    }
    else
    {
        // set a temp node* to the current list value
        node* temp = list[hash];
        while(temp->next != nullptr)
        {
            // First check for if there is the same value
            if(temp->data == in) throw ItemExistsException();
            out++;
            HASH_COUNT
            temp = temp->next;
        }
        temp->next = nnode;
        nnode->prev = temp;
    }

    length++;
    return out;
}


/*
    The find function will follow the given list untill
    it reaches the end or it can find the value which it was
    wanting to find
*/
node* Hash_2D::find(int in)
{
    // Create the hash to then find the index to search
    int hash = this->hash(in);

    // Check the first value and then the rest until the end
    // of the line is reached
    node* temp = list[hash];
    while(temp != nullptr)
    {
        HASH_COUNT
        if(in == temp->data)
        {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr;
}


// Create a remove function which will throw an exception
// if it can't find the given value

int Hash_2D::remove(int in)
{
    // Create the hash to then find the index to search
    int hash = this->hash(in);

    // Check the first value and then the rest until the end
    // of the line is reached
    node* temp = list[hash];
    while(temp != nullptr)
    {
        HASH_COUNT
        if(in == temp->data)
        {
            // Now that it has found it
            // ensure the list will remain consistent
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            // if there is a nullptr it should remain preserved in
            // this operation

            delete temp;
            this->length--;
            return in;
        }

        temp = temp->next;
    }

    throw ItemNotFoundException();
}

/*
    The print function will return each item and if it
    contains a list of them then the whole list as well, 
    with the hashes put at the front
*/

void Hash_2D::print()
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
            node* temp = list[i];
            cout << this->hash(temp->data) << " | " << temp->data;
            while(temp->next != nullptr)
            {
                cout << " --> " << temp->next->data;
                temp = temp->next;
            }
            cout << endl;
        }
    }
}

/*
    Simple hash which will use the modulus function
    to create the hashes in a simple manner
*/
int Hash_2D::hash(int in)
{
    return in % Max_Size;
}