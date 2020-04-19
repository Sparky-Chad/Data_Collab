#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>


// Set up counter macros
#ifdef COUNTER
extern int hashspot;
#define HASH_COUNT hashspot++;
#else
#define HASH_COUNT
#endif

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T* data;
        Node* next = nullptr;
        Node* previous = nullptr;
    };

    // Holds the value of the top of the list
    Node* head;
    
    // Holds the current node pointed at
    mutable Node* current;
public:
    // Constructor
    LinkedList()
    {
        head = nullptr;
        current = nullptr;
    }
    // Copy Constructor
    LinkedList(const LinkedList<T>& in);

    // Destructor
    ~LinkedList();

    // Method Functions
    void addItem(T*);
    T* getItem(T);
    bool isinList(T);
    bool isEmpty();
    int Size();

    T* SeeNext();
    T* SeePrev();
    T* SeeAt(int);
    void Reset();
    void Draw();

    LinkedList<T>& operator=(const LinkedList<T>& in);
    // Exceptions
    class ListIsEmpty
    {
    public:
        std::string print = "List is empty\n";
    };

    class NotInListException
    { public: std::string print() {return "Item not Found\n"; } };

};

// Deep Copy Constructor
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& in)
{
    this->head = nullptr;
    this->current = nullptr;

    Node* temp = in.head;
    Node* my_temp = this->head;
    T* temp_dat = nullptr;
    Node* nnode = nullptr;

    if(temp != nullptr)
    {
        temp_dat = new int(0);
        memcpy(temp_dat, temp->data, sizeof(temp->data));
        nnode = new Node{temp_dat};
        // Set so the head is now this
        head = nnode;

        temp = temp->next;
        while(temp != nullptr)
        {
            temp_dat = new int(0);
            memcpy(temp_dat, temp->data, sizeof(Node::data));
            nnode = new Node{temp_dat};

            my_temp->next = nnode;
            my_temp->next->previous = my_temp;

            my_temp = my_temp->next;

            temp = temp->next;

        }
    }
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& in)
{
    this->head = nullptr;
    this->current = nullptr;

    Node* temp = in.head;
    Node* my_temp = this->head;
    T* temp_dat = nullptr;
    Node* nnode = nullptr;

    if(temp != nullptr)
    {
        temp_dat = new int(0);
        memcpy(temp_dat, temp->data, sizeof(temp->data));
        nnode = new Node{temp_dat};
        // Set so the head is now this
        head = nnode;
        my_temp = head;
        temp = temp->next;
        while(temp != nullptr)
        {
            temp_dat = new int(0);
            memcpy(temp_dat, temp->data, sizeof(Node::data));
            nnode = new Node{temp_dat};

            my_temp->next = nnode;
            my_temp->next->previous = my_temp;

            my_temp = my_temp->next;

            temp = temp->next;

        }
    }

    return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    if(head == nullptr) return;
    Node* temp = head;
    while(temp->next != nullptr)
    {
        temp = temp->next;
        delete temp->previous;
        temp->previous = nullptr;
    }
    delete temp;
    temp = nullptr;
    head = nullptr;
    current = nullptr;
} 
template<class T>
void LinkedList<T>::addItem(T* in)
{

    Node* nnode = new Node{in};

    if(head == nullptr)
    {
        head = nnode;
        return;
    }

    Node* temp = head;

    // Run until the end of the list and if it reaches a point
    // where it can add above it will then stop and release it
    while(temp->next != nullptr)
    {
        HASH_COUNT
        if(temp->next->data < nnode->data)
        {
            nnode->previous = temp;
            temp = temp->next;
            nnode->previous->next = nnode;
            nnode->next = temp;
            temp->previous = nnode;
            return;
        }
        temp = temp->next;
    }

    // Other wise if this isn't the case then add the nnode to the
    // end of the linked list
    temp->next = nnode;
    nnode->previous = temp;
}

template <class T>
T* LinkedList<T>::getItem(T in)
{
    if(isEmpty()) throw ListIsEmpty();
    Node* temp = head;

    // This will handle if the data in the head file is the correct data to remove from the list.
    // This being the case, it will set head to the next which is fully compatible to how isEmpty()
    // handles a list being empty
    if(*temp->data == in)
    {
        head = temp->next;
        T* out = temp->data;
        delete temp;
        return out;
    }
    while(temp != nullptr)
    {
        HASH_COUNT
        if(*temp->data == *in)
        {

            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            T* out = temp->data;
            delete temp;
            return out;
        }
        temp = temp->next;
    }

    throw NotInListException();
}

template <class T>
bool LinkedList<T>::isinList(T in)
{
    Node* temp = head;
    while(temp != nullptr)
    {

        if(*temp->data == in)
        {
            return true;
        }
        temp=temp->next;
    }
    return false;
}

template <class T>
bool LinkedList<T>::isEmpty()
{
    if(head == nullptr)
    {
        return true;
    }
    return false;
}

template <class T>
int LinkedList<T>::Size()
{

    int i = 0;
    Node* temp = head;
    while(temp != nullptr)
    {
        temp = temp->next;
        i++;
    }
    return i;
}

template <class T>
T* LinkedList<T>::SeeNext()
{

    if(current == nullptr)
    {
        return nullptr;
    }
    else if(current->next != nullptr)
    {
        current = current->next;
        return current->data;
    }
    current = nullptr;
    return nullptr;
}

template <class T>
T* LinkedList<T>::SeePrev()
{
    if(isEmpty()) throw ListIsEmpty();

    if(current == nullptr) 
    {
        return nullptr;
    }
    else if(head == current)
    {
        current = nullptr;
        return nullptr;
    }
    current = current->previous;
    return current->data;
}

template <class T>
T* LinkedList<T>::SeeAt(int to)
{
    Node* temp = head;
    for(int i = 0; i < to; i++)
    {
        temp = temp->next;
    }
    current = temp;
    return temp->data;
}

// WIll delete each point in the linked list and then 
template <class T>
void LinkedList<T>::Reset()
{
    Node* temp = head;
    head = nullptr;
    current = nullptr;
    while(temp->next != nullptr)
    {
        temp = temp->next;
        delete temp->previous;
    }  
    delete temp;
}


template <class T>
void LinkedList<T>::Draw()
{
    using namespace std;
    Node* temp = head;
    cout << "Head" << endl;

    if(temp == nullptr)
    {
        cout << " |" << endl;
        cout << " |" << endl;
        cout << " ↓" << endl;
        cout << "nullptr\n\n\n";
        return;
    }
    cout << " |    nullptr" << endl;
    cout << " |      ^" << endl;
    cout << " ↓      |" << endl;
    cout << "Node | Prev | Data ---> " << *temp->data << endl;

    temp = temp->next;
    while(temp != nullptr)
    {
        cout << " | ^" << endl;
        cout << " | |-----" << endl;
        cout << " ↓      |" << endl;
        cout << "Node | Prev | Data ---> " << *temp->data << endl;

        temp = temp->next;
    }

    cout << " |" << endl;
    cout << " |" << endl;
    cout << " ↓" << endl;
    cout << "nullptr\n\n\n";
}

#endif