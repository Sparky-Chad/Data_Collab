

#include "Part.h"
#include "Linear_Hash.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include "stdlib.h"
#include "time.h"

// global list to make the other functions 
Linear_Hash<part> list = Linear_Hash<part>();

std::string choices = \
"1. Add Item to the Hash Table\n\
2. Remove Item from the List\n\
3. Check if Item is in the List\n\
4. Gets the size of the List\n\
5. Reset the List\n";
/*
5. Set Iterator at List position\n\
6. See the Next Iteration\n\
7. See the Previous Iteration\n\
8. Reset the List\n\
9. Draw the List\n";*/

int main()
{
    std::srand(std::time(NULL));
    bool again = true;
    // Only access parts off the linked list using the new operator with a pointer
    // otherwise this will result in malloc errors

    // This creates the initial header for the user
    
    do
    {
        int choice;
        // Create the header for the program which will give the user the initial choices
        std::cout << choices << std::endl;


    std::cout << "Operation to Perform: ";
        choice = -1;
        // Check if valid operation
        while(!(std::cin >> choice) || (choice < 0 || choice > 9))
        {            
            std::flush(std::cout);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Bad Value" << std::endl << "\nOperation to Perform: ";
        }

        part* temp;
        // Use switch case to perform the operation
        switch(choice)
        {
            case 0:
            {
                using namespace std;
                cout << "[";
                for(int i = 0; i < 20; i++)
                {
                    int sku;
                    std::string d;
                    double p;
                    std::string uom;
                    int Q;

                    sku = rand() % 1000;
                    d = "this is the item of sku " + to_string(sku);
                    p = double((rand() % 100) / (rand() % 5 + 1));
                    uom = "Something";
                    temp = new part(sku, d, p, uom);
                    list.insert(temp);
                    temp = nullptr;
                    if(i == 0)
                    {
                        cout << sku;
                    }
                    else
                    {
                        cout << ", " << sku;
                    }                    
                }
                cout << "]\n\n";
                cout << "Added 20 Random Items\n\n";
            }
            break;

            case 1:
            {
                int sku;
                std::string d;
                double p;
                std::string uom;
                int Q;
                std::cout << "Would you like to enter in the Quantity on hand?(y/n): ";
                char in;
                cin >> in;

                std::cout << "\nEnter the SKU of the item: ";
                std::cin >> sku;
                std::cout << "Enter the description of the item:\n";
                std::cin.ignore();
                std::getline(std::cin, d);
                std::cout << "Enter the Price of the item: $";
                std::cin >> p;
                std::cout << "Enter the Unit of Measure: ";
                std::cin >> uom;
                
                if(in == 'y' || in == 'Y')
                {
                    std::cout << "Enter the Quantity on Hand: ";
                    std::cin >> Q;
                    temp = new part(sku, d, p, uom, Q);
                }
                else
                {
                    temp = new part(sku, d, p, uom);
                }
                cout << "\nEntering item into the Ordered list\n";
                // Add pointer to the list and then clean temp variable
                list.insert(temp);
                temp = nullptr;        
            }
            break;
            case 2:
            {
                // Creates a misc part which is then used to find the true one 
                // and display its values
                int sku;
                using namespace std;
                cout << "Enter the SKU of the item to find: ";
                cin >> sku;
                part* misc = new part(sku, "", 0, "");
                // Try to get item or output it is not found 
                temp = list.getItem(misc);
                if(temp == nullptr)
                {
                    cout << "\n**Item was not found in the list**\n\n";
                }
                else
                {
                    cout << "\nItem was found and removed contents are:\n\n";
                    cout << temp->GetPartInfo() << endl;
                }
                delete misc;
                delete temp;
                temp = nullptr;                
            }
            break;
            case 3:
            {
                // Creates a misc part which is then used to find the true one 
                // and display its values
                int sku;
                using namespace std;
                cout << "Enter the SKU of the item to find: ";
                cin >> sku;
                part* misc = new part(sku, "", 0, "");
                if(list.getItem(misc) != nullptr)
                {
                    cout << "Item was found in the list\n";
                }                
                else
                {
                    cout << "Item not found in the list\n";
                }
                delete misc;
            }
            break;
            case 4:
            {
                std::cout << "Size of list is: " << list.getLength() << std::endl; 
            }
            break;
            /*
            case 5:
            {
                int max = list.length() - 1;
                int i;
                using namespace std;
                cout << "Chose a value between 0 and " << max << " to go to: ";
                while(!(cin >> i) && (i < 0 || i > max))
                {
                    flush(cout);
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "BAD VALUE" << endl;
                    cout << "Chose a value between 0 and " << max << " to go to: ";

                }

                temp = list.SeeAt(i);
                cout << "Item was found and its contents are:\n\n";
                cout << temp->GetPartInfo() << endl << endl;
                temp = nullptr;
            }
            break;
            case 6:
            {
                if((temp = list.SeeNext()) != nullptr)
                {
                    std::cout << "Item at SeeNext is: \n\n";
                    std::cout << temp->GetPartInfo() << std::endl << std::endl;
                    temp = nullptr;
                }
                else
                {
                    std::cout << "The Iterator is not currently on the list\n\n";
                }
            }
            break;
            case 7:
            {
                if((temp = list.SeePrev()) != nullptr)
                {
                    std::cout << "Item at SeePrev is: \n\n";
                    std::cout << temp->GetPartInfo() << std::endl << std::endl;
                    temp = nullptr;       
                }
                else
                {
                    std::cout << "The Iterator is not currently on the list\n\n";
                }
                
            }
            break;
            */
            case 5:
            {
                std::cout << "Reseting the list\n\n";
                list.~Linear_Hash();
                list = Linear_Hash<part>();
            }
            break;
            /*
            case 9:
            {
                std::cout << "\n\n\n";
                std::flush(std::cout);
                list.Draw();
                std::flush(std::cout);
            }
            break;*/
        }
        

        std::cout << "Run again?(y/n): ";
        char in;
        std::cin >> in;
        again = in == 'y' || in == 'Y';
    } while(again);


    return 0;
}


// Generates 