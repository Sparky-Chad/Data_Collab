#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include "Word.h"

using namespace std;


template <class T>
class BinaryTree {

public:
	struct node {
		T data;
		struct node* right;
		struct node* left;
	};

	BinaryTree() {
		this->root = nullptr;
		this->size = 0;
		this->check_now = false;
	};

	~BinaryTree() {
		emptyTree();
	};

	void emptyTree();
	void insert(T);
	node* find(T);
	int gsize();
	node** getAllAscending();
	node** getAllDescending();
	void remove(T data);

	//exceptions
	class inTreeAlready{};

private:
	node* root;
	int size;
	void emptyTree(node*); //must input root to delete entire tree
	void insert(node*, T);
	node* find(node*, T);
	
	void getAllAscending(node** arr);
	void getAllDescending(node** arr);
	
	// Classes for balance checking

	// Iterates the all of the parents and pivot to the node in there
	// the left pivot and right pivot is returned
	void iterate(bool right, node* pivot, node* parent, node* gparent);
	// Returns an int as the current height of a node when balance checking
	int height(node*);

	// Get the height from one side of the node
	int left_height(node *);
	int right_height(node*);
	
	// boolean value so that every other operation it will check if it is balanced
	bool check_now;

	// Function to check if node is balanced
	bool is_balanced(int, int);

	bool is_balanced(node*);

	// Rotating right and left
	void rotate_right(node*, node*, node*);

	void rotate_left(node*, node*, node*);
	
	// balance the tree from the bottom up to the node at the top
	void recursively_balance(node*);

	// default to the root
	void recursively_balance();


};


#endif
template <class T>
void BinaryTree<T>::insert(T val) {
	insert(this->root, val);
}


template <class T>
void BinaryTree<T>::insert(BinaryTree<T>::node* nnode, T val) {

	if (*nnode == nullptr) {
		nnode->data = val;
		nnode->left = nullptr;
		nnode->right = nullptr;

		this->size++;
	}
	else {
		if (val > nnode->value) {
			insert(node->right, val);
		}
		if (val == nnode->value) {
			throw inTreeAlready();
		}
		else {
			insert(nnode->left, val);
		}
		this->size++;
	}


}


template <class T>
BinaryTree<T>::node* BinaryTree<T>::find(T val) {
	return find(root, val);
}

template <class T>
BinaryTree<T>::node* BinaryTree<T>::find(BinaryTree<T>::node* nnode, T val) {
	if (nnode == nullptr) {
		return nullptr;
	}
	else {
		if (val == nnode->value) {
			return node;
		}
		if (val > nnode->value) {
			return find(nnode->right, val);
		}
		else {
			return find(nnode->left, val);
		}
	}
}

template <class T>
int BinaryTree<T>::gsize() {
	return size;
}



template <class T>
BinaryTree<T>::node** BinaryTree<T>::getAllAscending() {
	
}


template <class T>
BinaryTree<T>::node** BinaryTree<T>::getAllDescending(){






}

template <class T>
void BinaryTree<T>::emptyTree()
{
	emptyTree(this->root);
	this->root = nullptr;
	this->size = 0;
	this->check_now = false;
}
//must input root to delete entire tree
template <class T>
void BinaryTree<T>::emptyTree(node* nnode) {
	if (node != nullptr) {
		emptyTree(nnode->right);
		emptyTree(nnode->left);
		delete nnode;
	}
}
template <class T>
void BinaryTree<T>::remove(T data) {

	if(this->root = nullptr) return nullptr;
	node* gparent = this->root;
	node* parent = this->root;
	node* temp = this->root;
	while (temp != nullptr && temp->value != data)
	{
		if(temp->value < data)
		{
			this->iterate(true, temp, parent, gparent);
		}
		else if(temp->value > data)
		{
			this->iterate(false, temp, parent, gparent);
		}
	}

	if(temp->value != data) return nullptr;
	
	// Everything else will handle if node is a root
	// Now we need to recursively move the node down

	if(this->right_height(temp) > this->left_height(temp))
	{
		this->iterate(true, temp, parent, gparent);
		this->rotate_right(temp, parent, gparent);
		// Now it is at the extreme it could be at
		gparent->left = nullptr;
	}
	else 
	{
		this->iterate(false, temp, parent, gparent);
		this->rotate_left(temp, parent, gparent);
		gparent->right = nullptr;
	}
	delete parent;

	size--;

}

// This will iterate the tree so that there can be a new iteration of the pivots
template <class T>
void BinaryTree<T>::iterate(bool right, BinaryTree<T>::node* pivot, BinaryTree<T>::node* parent, BinaryTree<T>::node* gparent)
{
	gparent = parent;
	parent = pivot;
	if(right)
	{
		pivot = pivot->right;
	}
	else
	{
		pivot = pivot->left;
	}
	
	return;
}

template <class T>
int BinaryTree<T>::height(node* in)
{
	int left = left_height(in);
	int right = right_height(in);

	if(left > right) return right;
	return left;
}

template <class T>
int BinaryTree<T>::left_height(node* in)
{
	if(in->left == nullptr) return 1;

	return 1 + left_height(in->left);
}

template <class T>
int BinaryTree<T>::right_height(node* in)
{
	if(in->right == nullptr) return 1;

	return 1 + right_height(in->right);
}

template <class T>
bool BinaryTree<T>::is_balanced( int left, int right)
{
	// get the abs of the difference
	int diff = left - right;
	if(diff < 0) diff = diff * -1;

	// Return if the difference between the two sizes is bigger than 2
	return diff > 2;
}

template <class T> 
bool BinaryTree<T>::is_balanced(node* in)
{
	return is_balanced(left_height(in), right_height(in));
}

template <class T>
void BinaryTree<T>::rotate_right(node* pivot, node* parent, node* gparent)
{

	if(parent == root)
	{
		root = pivot;
	}
	// Check which side of the gparent is being rotated
	if(gparent->left == parent)
	{
		gparent->left = pivot;
	}
	else
	{
		gparent->right = pivot;
	}

	// Remove the reference which points back to the pivot
	parent->right = nullptr;

	// Because we are rotating to the right we need to move the parent to the absolute
	// left of the pivot, this may unbalence tree and as such we must recursively rebalance
	// to the current pivot
	node* temp = pivot;
	while(temp->left != nullptr)
	{
		temp = temp->left; 
	}
	temp->left = parent;
	gparent = temp;
	recursively_balance(pivot);
}

template <class T>
void BinaryTree<T>::rotate_left(node* pivot, node* parent, node* gparent)
{
	if(parent == root)
	{
		root = pivot;
	}
	// Check which side of the gparent is being rotated
	if(gparent->left == parent)
	{
		gparent->left = pivot;
	}
	else
	{
		gparent->right = pivot;
	}

	parent->left = nullptr;

	// Because we are rotating to the right we need to move the parent to the absolute
	// left of the pivot, this may unbalence tree and as such we must recursively rebalance
	// to the current pivot
	node* temp = pivot;
	while(temp->right != nullptr)
	{
		temp = temp->right; 
	}
	temp->right = parent;
	temp = gparent;

	recursively_balance(pivot);
}



//reference: https://gist.github.com/toboqus/7a7b3d334c9ac59f3d5a