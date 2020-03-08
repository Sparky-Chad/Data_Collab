
#include <iostream>
#include "OrderedList.h"
#include "BlanksOrderedList.h"

int main() { 
    // testing use of bool to run it
    int outt = (2 * true) - 1;
    int outf = (2 * false) - 1;
    std::cout << "True = " << outt << std::endl << "False = " << outf << std::endl;

    // Create a new OrderedList to begin testing it
    OrderedList nlist<int> = OrderedList();

    for(int i = 0; i < 25; i++)
    {
        nlist.addItem(i);
    }

    for(int i = 0; i < 25; i++)
    {
        if(nlist.removeItem(4) == 4)std::cout << "nlist has item 4" << std::endl;
         if(nlist.removeItem(9) == 9)std::cout << "nlist has item 9" << std::endl;
         try
         {

             if(nlist.removeItem(9) == 9)std::cout << "nlist has item 9" << std::endl;
         }
         catch(OrderedList<int>::ItemNotDefinedException())
         {
             cout << "Caught that the list does not have 9 twice" << endl;
         }
            
    }
}
