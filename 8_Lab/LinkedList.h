#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T* data;
        Node* next;
        Node* previous;
    };

    // Holds the value of the top of the list
    Node* head;
    
    // Holds the current node pointed at
    Node* current;
public:
    // Constructor
    LinkedList()
    {
        head = nullptr;
        current = nullptr;
    }

    // Destructor
    ~LinkedList();

    // Method Functions
    void addItem(T*);
    T* getItem(T*);
    bool isinList(T*);
    bool isEmpty();
    int Size();

    T* SeeNext();
    T* SeePrev();
    T* SeeAt(int);
    void Reset();


    // Exceptions
    class ListIsEmpty
    {};


};

 
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
        if(temp->next->data < nnode->data)
        {
            nnode->previous = temp;
            temp = temp->next;
            nnode->previous->next = nnode;
            nnode->next = temp;
            temp->previous = nnode;
            return;
        }
    }

    // Other wise if this isn't the case then add the nnode to the
    // end of the linked list
    temp->next = nnode;
    nnode->previous = temp;
}

template <class T>
T* LinkedList<T>::getItem(T* in)
{
    if(isEmpty()) throw ListIsEmpty();
    Node* temp = head;

    // This will handle if the data in the head file is the correct data to remove from the list.
    // This being the case, it will set head to the next which is fully compatible to how isEmpty()
    // handles a list being empty
    if(*temp->data == *in)
    {
        head = temp->next;
        return temp;
    }
    while(temp != nullptr)
    {
        if(*temp->data == *in)
        {

            temp->previous->next = temp->next;
            temp->next->previous = temp->previous;
            return temp;
        }
    }

    return nullptr;
}

template <class T>
bool LinkedList<T>::isinList(T* in)
{
    T* temp = head;
    while(temp != nullptr)
    {

        if(*temp->data == *in)
        {
            return true;
        }

    ()}
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
T*


#endif
