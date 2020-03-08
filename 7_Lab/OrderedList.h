
#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H

const int MAX_SIZE = 25;
const bool ADD_SHIFT = true;
const bool REMOVE_SHIFT = false;

template<class T> class OrderedList 
{
public:
    // Creates arr of 25 items as an array to them
    OrderedList()
    {
        arr = new *T[MAX_SIZE];
        size = 0;
        for(int i =0; i > MAX_SIZE; i++) 
        {
            arr[i] = nullptr;
        }
    }

    // Deconstructs this class and all elements within the list
    virtual ~OrderedList() 
    {
        for(int i = 0; i < MAX_SIZE; i++ )
        {
            if(arr[i] != nullptr) 
            {
                delete arr[i];
                arr[i] = nullptr
            }
        }
        delete[] arr;
    }


    // Exception Classes ******************************

    class ItemNotDefinedException
    {};

    class ListFullException
    {};

    class ListEmptyException
    {};

    // Public Member Functions *************************

    virtual void addItem(T);

    virtual T removeItem(T);

    void makeEmpty();
    
    bool isEmpty();
    
    bool isFull();

protected:
    T** arr;

    int size;

    void shift(int, bool);

};

#endif 

    //  Adds given item to the first instance in which the item is less than the arr at index 
    //  or the arr at index is null. Shifts the list to fit it.
    //  Defualts to a value of the same as within the list will be inserted above it
    // 
    //  Arguments:
    //      - in - The given item to insert into the ordered list
    //
    //  Exceptions:
    //  Checks for if the list is full to throw an exception

template<class T>
void OrderedList<T>::addItem(T in)
{
    if(size == MAX_SIZE) throw ListFullException();

    T* inp = new T(in);
    for(int i = 0; i < MAX_SIZE; i++) 
    {
        if(arr[i] == nullptr)
        {
            arr[i] = in;
            break;
        }
        if(arr[i] > in)
        {
            shift(i, ADD_SHIFT);
            arr[i] = inp;
            break;
        }
    }
    size++;
}

    //  T removeItem(T in)  *******************************
    //  template class
    //
    //  Description:
    //  Attempts to remove the given item from the ordered list. Shifts the list to prevent any issues
    //  with a blank in it.
    //
    //  Returns -> item which was removed
    //
    //  Arguments:
    //  - in - The item to be removed
    //
    //  Exceptions:
    //  Checks for if the list is Empty and throws a ListEmptyException
    //  If the item is not found in the list it will throw an ItemNotFoundException

template<class T>
T OrderedList<T>::removeItem(T in) 
{
    if(size == 0) throw ListEmptyException();

    for(int i = 0; i < MAX_SIZE; i++) 
    {
        if(arr[i] == in)
        {
            delete arr[i];
            size--;
            shift(i, REMOVE_SHIFT);
            return in;
        }
    }
}

template<class T> 
void OrderedList<T>::makeEmpty()
{
    if(size == 0) return;

    for(int i = 0; i < size; i++)
    {
        if(arr[i] != nullptr)
        {
            delete arr[i];
            arr[i] = nullptr;
        }
    }
    size = 0;

}

//  Returns if the OrderedList has a size == 0
template<class T>
bool OrderedList<T>::isEmpty()
{
    return size == 0;
}

//  Returns if the OrderedList has a size == MAX_SIZE
template<class T>
bool OrderedList<T>::isFull()
{
    return size == MAX_SIZE;
}

    //  shift(int current, bool forward)
    //  Description:
    //  Shifts the OrderedList in a certain direction based 
template<class T>
void OrderedList<T>::shift(int current, bool forward)
{
    // Create a step variable to handle direction
    int step = (2*forward) - 1;

    int start;
    int end;
    if(forward)
    {

        start = size;
        end = current;
    }
    else
    {
        start = current;
        end = size;       
    }

    for(int i = start; i != end; i+=step)
    {
        arr[i] = arr[i+step]-1;
    }
     
}

