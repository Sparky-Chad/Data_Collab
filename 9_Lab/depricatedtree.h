#ifndef CATALOGTREE_H
#define CATALOGTREE_H

#define _ITEM_EXISTS_MESSAGE_ "Item Given Already Exists within the Tree\n"

// Include strings
#include <string>
// Include Word class
#include "Word.h"

// Structure data type to be used for the rest of the tree and can be used with
// the other stuff
struct node
{
    Word* data;
    node* right = nullptr;
    node* left = nullptr;
};

class CatalogTree
{

private:

    node* root;

public:

    // Constructors
    CatalogTree() { root = nullptr; }

    // Deconstructors
    ~CatalogTree();

    // Methods 

    // Insert
    // Must ensure the tree remains centered within 2 levels of itself so no side is to long
    // Inserts item into the tree
    // Possibly have some path variable which keeps track of this and then maybe decides whether it is supposed to rebalance some elements
    void insert(Word);

    // Find
    // Gets the element from the list following the binary tree does not remove the item and returns a pointer to the node
    Word* find(Word);

    // Remove
    // removes the node from the tree without deallocating it and returns the pointer to it
    node* remove(Word);

    // GetAllAscending
    // Returns a dynamically created pointer array which is an array of all nodes in ascending order
    node* GetAllDescending(node*);
    // Overload
    // gets all ascending from the root
    node* GetAllAscending();

    // GetAllDescending
    // Returns a dynamically created pointer array which is an array of all nodes in descending order
    node* GetAllDescending(node*);
    // Overload
    // Returns from root node
    node* GetAllDescending();

    // EmptyTree
    // Deallocates all of the nodes within the binary tree
    void EmptyTree();

    // Exceptions
    class ItemExistsException
    { public: std::string print() {return _ITEM_EXISTS_MESSAGE_;}};
};

#endif