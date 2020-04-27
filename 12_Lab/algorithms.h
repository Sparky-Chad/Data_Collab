#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <cmath>
#include "Queue.h"
#include <iostream>


// This quick macro will just work to output results of arr in any algorithm
// comment printdebug to disable this
    #define PRINTDEBUG

#ifdef PRINTDEBUG
#define ARR_PRINTER \
            std::cout << "\nbeing sorted arr = ["; \
            std::cout << arr[0]; \
            for(int i = 1; i < size; i++) {\
                std::cout << ", " << arr[i]; \
            } \
            std::cout << "]";
#else
#define ARR_PRINTER
#endif

// This will conatin a functions for algorithms in use through lab 12
// using the namespace algorithms so as to reduce possibility of name collision


class radixException
{};
/*
    All of these algorithms will work with dynamic arrays sent through pointers. As such any 
    data type should be able to convert to and from this format
*/
namespace algorithms
{

    // Serves as a standard function pointer type
    typedef void (*algorithm)(int*, int);

    /*
        Radix function
        necesitates the size of array being pased and the if possible the maximum digit it will pass through

        the pass through digit however will be optional and if not set the function will continue n+1 times with n being
        the moment which 1 data still has digits or n+1 where no data has another digit to process. 

        The function will also keep the current smallest index. this being the point by which data beneath no longer have any
        digits at this level. This should somewhat help to optimize higher w costs for n so that the time length can be somewhat
        cheaper.
        
        varaibles
        ints:
        i, j, ee
    */

    void radix(int* arr, int size)
    {
        // Variable which defines to the to while loop whether it should continue
        bool relevant = true;

        // Set up variables for use within the program
        int counter, ee = 0, i = 0, j=0, temp, minimum = 0, rel_count=1;

        // Uses queues to store variables in boxes
        Queue<int> boxes[10];

        do
        {
            counter = 0;

            // Enque boxes section
            for(i = minimum; i < size; i++)
            {
                temp = arr[i];

                temp = (int(temp/pow(10, ee))%10);

                if(temp > 0) counter++;
                boxes[temp].enque(arr[i]);
            }   

            j = minimum;
            // Dequeue boxes section
            for(i = 0; i < 10; i++)
            {
                while(!boxes[i].checkempty())
                {
                    // if j is > size then a critical error has occured somewhere
                    // as it means that j has somewhere failed
                    if(j > size) throw radixException();
                    try
                    {
                        arr[j] = boxes[i].deque();
                    }
                    catch(Queue<int>::UnderflowException)
                    {
                        // queue has failed somehow
                        std::cout << "radix underflow exception\n";
                        throw radixException();
                    }
                    j++;
                    if(j >= size) break;
                }
                boxes[i].empty();
                if(j >= size) break;
            }
            relevant = counter > 0;
            if(!relevant && rel_count)
            {
                rel_count--;
                relevant = true;
            }
            ARR_PRINTER
            ee++;
        } while (relevant);
    }



    /*
        This will be a counting sort array.

        creates an array the size of the maximum value within the to sort array. Then it gives out
        an array of size of the other.
    */

   void counting(int* arr, int size)
   {
        int max_size = -1;
        for(int i = 0; i < size; i++)
        {
            if (arr[i] > max_size) max_size = arr[i];
        }

        // Create array of max size
        int* counter = new int[max_size+1];
        for(int i = 0; i <= max_size; i++) 
            counter[i] = 0;

        // run through and counter the variables
        for(int i = 0; i < size; i++) 
            counter[arr[i]]++;

        // Add the index they should go to
        int index = 0;
        for(int i = 0; i <= max_size; i++)
        {
            if(counter[i] != 0)
            {
                counter[i] += index;
                index = counter[i];
            }
        }
        int* output = new int[size];
        for(int i = 0; i < size; i++)
            output[counter[arr[i]]-- - 1] = arr[i];

        for(int i = 0; i < size; i++)
            arr[i] = output[i];
        
        ARR_PRINTER
   }

   void quicksort(int* arr, int size)
   {
       int pivot;
       if(size > 10)
       {
           int first = arr[0], middle = arr[size/2], last = arr[size];

           


       }
   }

}



#endif