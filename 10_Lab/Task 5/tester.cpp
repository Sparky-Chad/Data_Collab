#include "counter.h"
#include "Part.h"
#include "hash_2d.h"
#include "Linear_Hash.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include "stdlib.h"
#include "time.h"

extern int searchspot;
extern int hashspot;
using namespace std;
// global list to make the other functions 
Hash_2D<part> list = Hash_2D<part>();
Linear_Hash<part> llist = Linear_Hash<part>();

#define sizer 250
int arr[sizer];
int main()
{
    part* temp;
    cout << "[";
    for(int i = 0; i < sizer; i++)
    {
        int sku;
        std::string d;
        double p;
        std::string uom;
        int Q;

        sku = rand() % 9000;
        arr[i] = sku;
        d = "this is the item of sku " + to_string(sku);
        p = double((rand() % 100) / (rand() % 5 + 1));
        uom = "Something";
        temp = new part(sku, d, p, uom);
        list.insert(temp);
        llist.insert(temp);
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
    cout << "Added 50 Random Items\n\n";

    cout << "Removing items from the array\n";
    for(int i = 0; i < sizer; i++)
    {
        cout << "Getting:\n";

        cout << i << ":" << endl;
        temp = new part(arr[i], "", 0, "");
        part* out = list.getItem(temp);
        llist.getItem(temp);
        delete temp;
        cout << out->GetPartInfo() << endl << endl;
    }
    cout << "Values: " << "\nLinear: " << searchspot << "\n2D_Hash: " << hashspot << endl;
}