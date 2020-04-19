#ifndef QUEUE_H_
#define QUEUE_H_

#include <cstdlib>
#include <stdlib.h>
#include <exception>

template <class T>
class Queue {
    public:
    // Constructors for the Queue, these will input a variable which
    // will create the size of the array
    Queue(int in);

    // Destructor will handle cleaning the entirty of the array of pointers
    ~Queue()
    {
        empty();
        // Call empty to activate the destructor
        delete[] arr;
    }

    // Class member functions

    // Empties the queue and deletes the values 
    void empty();      

    // Adds a pointer to the pointer queue
    void enque(T*);

    // Removes a pointer from the front of the pointer queue
    T* deque();
    
    // Returns the pointer to the first value without changing it
    T* peek();

    // Returns the length of the queue
    int length();

    // Check if queue is full
    bool checkfull();

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
    // Create a pointer to the array the Queue will handle to enable dynamic
    // array creation and handling
    T** arr;
    // Keeps the position of the top of the Queue
    int front;
    // Holds the position of the back of the Queue 
    int back;

    int max_size;
};

#endif


// Implementation in h file due to template class status
// Constructor implementation
template <class T> 
Queue<T>::Queue(int in) {
    max_size = in;
    arr = new T*[max_size];
    front = 0;
    back = 0;
    size = 0;

    // initiallize as null pointers
    for(int i = 0; i < max_size; i++) {
        arr[i] = nullptr;
    }
}

//Empty the queue
template <class T>
void Queue<T>::empty() {
    // delete pointer values to avoid memory issues
    for(; front < back; front++) {
    if (arr[front] != nullptr) {
            try {
                delete (arr[front]);
            }
            // attempt to deallocate the memory
            // however if this fails then the memory is 
            // statically allocated and the ptr should be to
            // null instead
            catch(std::exception& e) {
                arr[front] = nullptr;
            }
        }
    }

    // reset front and back
    back = front;

    // reset size
    size = 0;

}

// Adds 
template <class T>
void Queue<T>::enque(T* in) {
    //Check if the array is full for a stack overflow
    if(checkfull()) {
        throw OverflowException();
    }

    // add to the back 
    arr[back] = in;

    // Use the remainder to send to zero if it is max size
    // this works as the remainder will always be equal to the
    // numerator if it is < the denominator
    back = (back + 1) % max_size;
    size++;
    
}

// Removes from the front of the queue
template <class T> 
T* Queue<T>::deque() {
    // Check if the queue is empty
    if(checkempty()) {
        throw UnderflowException();
    }

    // take the rearmost pointer to return
    T* temp = arr[front];


    // Refer to enque change
    front = (front + 1) % max_size;
    size --;

    return temp;
}

// Returns the first pointer without removing the value
template <class T>
T* Queue<T>::peek() {

    if (checkfull()) {
        throw OverflowException();
    }
    return arr[front];

}

// returns the length of the Queue
template <class T>
int Queue<T>::length() {
    return size;
}

// Returns a bool of whether size is the max size
template <class T>
bool Queue<T>::checkfull() {
    return size==max_size;
}

// Returns a bool of whether the the queue size is zero
template <class T>
bool Queue<T>::checkempty() {
    return size==0;
}
