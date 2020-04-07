// Have this with some test cases to see if the binary tree works predictably

#include "BinaryTree.h"

#include "iostream"
#include "string"


using namespace std;

int main()
{
    BinaryTree<int> tree;
    tree = BinaryTree<int>();

    cout << "Beginning to add elements";

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(-5);
    tree.insert(-6);

    cout << "Removing a thing " << tree.remove(3)->data << endl;
    

    return 0;
}