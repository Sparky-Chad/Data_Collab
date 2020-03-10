#ifndef _BLANKSORDEREDLIST_H_
#define _BLANKSORDEREDLIST_H_

#include "OrderedList.h"
#include <math.h>
namespace blanks {
    template<class T> class BlanksOrderedList : public OrderedList<T>
    {
    public:

        BlanksOrderedList():OrderedList<T>{}
        {}

        // Redefines the addItem class
        void addItem(T);

        T remove(T);



        // Unable to find blank space exception
        class BlankNotFoundException
        {};

        // Unable to find the item exception
        class ItemNotFoundException
        {};
    private:
        // Finds the next viable index to move to
        int find_next_item(int, bool);

        // Finds the next or previous empty space
        int find_next_blank(int, bool);

        // Shifts values to blank space and inserts address into arr
        void shift_list(int, int);

        int find_nearest_blank(int);
    };
}
#endif

/*  This version will begin its look at the begining of the class and actively ignore nullptrs
*   
*   The values of next and prev are holding the potential ints for the values next to the current index without
*   counting nullptr values.
*/
template<class T> void blanks::BlanksOrderedList<T>::addItem(T in) 
{
    // Check if it is full and throw exception if so
    if(this->checkFull())
    {
        throw this->ListFullException();
    }

    T* inp = new T(in);

    if(size == 0)
    {
        arr[0] = T;
        return;
    }

    // i begins at the first index where an item exists
    for(i = find_next_item(-1); i < MAX_SIZE;) {

        //  Special case if i is at beginning
        //  Evaluates whether it can replace the first value or to search 
        //  to the next occupied index of the array
        if(in >= *arr[i]) {
            i = this->find_next_item(i);
            continue;
        }
        else {

            // gets nearest blank and then shifts array in that direction
            int nearest_blank = find_nearest_blank(i);

            // Shifts the array in that direction to the blank
            shift_list(i, nearest_blank);

            arr[i] = inp;

        }
    }
    size++;
}

    //  Removes the given class item from the list after searching for it
    //  Arguements:
    //      - in - Object to search for
    //
    //  If the size is 0 it will throw a list empty exception
    //
    //  if the item is not found it will throw an item not found exception

template<class T> T blanks::BlanksOrderedList<T>::remove(T in) 
{

    if(size == 0) throw ::OrderedList<T>::ListEmptyException();

    for(int i = find_next_item(-1); i < MAX_SIZE; i = find_next_item(i))
    {
        if(*arr[i] == in) 
        {
            delete arr[i];
            size--;
            return in;
        }
    }

    throw ItemNotFoundException();
}

    // Recieve the current index of the list and then return the next index with an item pointed to
    //
    //  Uses two arguments:
    //      - current - the current index the array is at
    //      - forward = true - value which declares if stepping forward in the array or back with default value of true
    //  
    //  The function iterates by atleast +||- 1 and will continue till the first iteration of it
    //
template <class T> int blanks::BlanksOrderedList<T>::find_next_item(int current, bool forward=true) {

    // Create iterator value which will be used to step through arr by using the value of a bool being 1 or 0
    // to then use as the stepping value.
    int step = (2 * forward) - 1;

    do {
        current += step;

    } while(arr[current] == nullptr)

    return current;
}

    // Recieve the current index of the list and then return the next index which is pointing to nullptr
    //
    //  Uses two arguments:
    //      - current - the current index the array is at
    //      - forward = true - value which declares if stepping forward in the array or back with default value of true
    //  
    //  The function iterates by atleast +||- 1 and will continue till the first iteration of it
    //
template <class T> int blanks::BlanksOrderedList<T>::find_next_blank(int current, bool forward=true) {

    // Create iterator value which will be used to step through arr by using the value of a bool being 1 or 0
    // to then use as the stepping value.
    int step = (2 * forward) - 1;

    do {
        current += step;

    } while(arr[current] != nullptr && current < MAX_SIZE && current >= 0);

    return current;
}

    // Searches ahead of the function and behind it to find the nearest index within the bounds of the array
    // Will throw an error if the size of the array is max or if it does not find a blank within its bounds
    //
    // Uses one argument:
    //      - current - the index which the 
    //
    // Uses the if statements to determine if the indexs found are within bounds and which one is closer to remove
template <class T> int blanks::BlanksOrderedList<T>::find_nearest_blank(int current)
{
    if(size >= MAX_SIZE) throw ::OrderedList<T>::ListFullException();

    int forward = find_next_blank(current);
    int backward = find_next_blank(current, false);

    if((forward >= MAX_SIZE || forward < 0) && (backward >= MAX_SIZE || backward < 0)) {
        throw BlankNotFoundException();
    }
    else if((forward >= MAX_SIZE || forward < 0))
    {
        return backward;
    }
    else if(backward >= MAX_SIZE || forward < 0)
    {
        return forward;
    }
    else if(backward < forward)
    {
        return backward;
    }
    else 
    {
        return forward;
    }
}


    // Inserts element int the pointer array. 

template <class T> void blanks::BlanksOrderedList<T>::shift_list(int current, int open) 
{
    int step;
    if(current > open)
    { step = 1; }
    else 
    { step = -1; }

    for(int i = open; i <= current; i += step) 
    {
        arr[open] = arr[i];
        open = i;
    }
}
