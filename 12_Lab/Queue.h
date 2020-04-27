#ifndef QUEUE_H_
#define QUEUE_H_

#include <cstdlib>
#include <stdlib.h>
#include <exception>
#include "LinkedList.h"


template <class T>
class Queue: protected LinkedList<T>
{
    public:
    // Constructors for the Queue, these will input a variable which
    // will create the size of the array
    Queue();

    // Destructor will handle cleaning the entirty of the array of pointers
    ~Queue()
    {
        empty();
    }

    // Class member functions

    // Empties the queue and deletes the values 
    void empty();      

    // Adds a pointer to the pointer queue
    void enque(T);

    // Removes a pointer from the front of the pointer queue
    T deque();
    
    // Returns the pointer to the first value without changing it
    T* peek();

    // Returns the length of the queue
    int length();

    // Check if the queue is empty
    bool checkempty();


    // Exception classes
    class OverflowException 
    {};
    class UnderflowException
    {};

private:
    // hold the size of the queue to then check for errors
    int size;

    // Holds the position of the back of the Queue 
    typename LinkedList<T>::Node* rear;


    using LinkedList<T>::head;

};

#endif


// Implementation in h file due to template class status
// Constructor implementation
template <class T> 
Queue<T>::Queue() : LinkedList<T>::LinkedList{} {
    this->rear = nullptr;
    this->size = 0;
}

//Empty the queue
template <class T>
void Queue<T>::empty() {

    this->Reset();
    this->rear = nullptr;
    this->size = 0;

}

// Adds 
template <class T>
void Queue<T>::enque(T in) {


    // Check if the current linked list has 
    typename LinkedList<T>::Node* nnode = new typename LinkedList<T>::Node{new T(in)};

    if(this->rear == nullptr) this->rear = nnode;
    if(this->head != nullptr) this->head->previous = nnode;
    nnode->next = this->head;
    this->head = nnode;

    this->size++;
}

// Removes from the front of the queue
template <class T> 
T Queue<T>::deque() {

    if(this->rear == nullptr) throw UnderflowException();

    if(rear->previous != nullptr)
    {
        typename LinkedList<T>::Node* temp = this->rear;
        this->rear = this->rear->previous;

        int out = *temp->data;
        delete temp->data;
        delete temp;

        this->rear->next = nullptr;
        size--;
        return out;
    }
    else
    {
        int out = *this->rear->data;
        delete rear->data;
        delete rear;
        this->rear = nullptr;
        this->size=0;
        return out;
    }
}

// Returns the first pointer without removing the value
template <class T>
T* Queue<T>::peek() {

    return *this->rear->data;

}

// returns the length of the Queue
template <class T>
int Queue<T>::length() {
    return this->side;
}

// Returns a bool of whether the the queue size is zero
template <class T>
bool Queue<T>::checkempty() {
    return this->size==0;
}
