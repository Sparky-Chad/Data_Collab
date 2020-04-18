#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

#define UPWARD true
#define DOWNWARD false

#ifdef COUNTER
extern int binaryspot;
#define COUNT_BINARY binaryspot++;
#else
#define COUNT_BINARY
#endif

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
	node* remove(T data);

	//exceptions
	class inTreeAlready
	{
	public: string print() { return " Item is Located in tree Already"; }
	};

private:
	node* root;
	int size;
	void emptyTree(node*); //must input root to delete entire tree
	void insert(node**, T);
	node* find(node*, T);

	int getAllArray(node** arr, bool ascending, node* temp = nullptr, int i = 0);

	// Classes for balance checking

	// Iterates the all of the parents and pivot to the node in there
	// the left pivot and right pivot is returned
	void iterate(bool right, node* pivot, node* parent, node* gparent);
	// Returns an int as the current height of a node when balance checking
	int height(node*);

	// Get the height from one side of the node
	int left_height(node*);
	int right_height(node*);

	// boolean value so that every other operation it will check if it is balanced
	bool check_now;

	// Function to check if node is balanced
	bool is_balanced(int, int);

	bool is_balanced(node*);

	// Rotating right and left
	node* rotate_right(node* parent, node* gparent = nullptr);

	node* rotate_left(node* parent, node* gparent = nullptr);

	// balance the tree from the bottom up to the node at the top
	void recursively_balance(node* parent = nullptr, node* gparent = nullptr);

};


#endif
template <class T>
void BinaryTree<T>::insert(T val) {
	insert(&(this->root), val);
}


template <class T>
void BinaryTree<T>::insert(BinaryTree<T>::node** nnode, T val) {

	node* temp;
	node* iter = *nnode;
	if (iter == nullptr) {
		temp = new node;
		temp->data = val;
		temp->left = nullptr;
		temp->right = nullptr;

		*nnode = temp;
		this->size++;


		if (this->check_now)
		{
			this->recursively_balance();
			this->check_now = false;
		}
		else
		{
			this->check_now = true;
		}
	}
	else {
		COUNT_BINARY
			if (val > iter->data) {
				nnode = &(iter->right);
				insert(nnode, val);
			}
			else if (val == iter->data) {
				nnode = &(iter->right);
				insert(nnode, val);
			}
			else {
				nnode = &(iter->left);
				insert(nnode, val);
			}
	}


}

template <class T>
typename BinaryTree<T>::node* BinaryTree<T>::find(T val) {
	return find(root, val);
}

template <class T>
typename BinaryTree<T>::node* BinaryTree<T>::find(node* nnode, T val) {
	if (nnode == nullptr) {
		return nullptr;
	}
	else {
		COUNT_BINARY
			if (val == nnode->data) {
				return nnode;
			}
		if (val > nnode->data) {
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
typename BinaryTree<T>::node** BinaryTree<T>::getAllAscending()
{
	node** out = new node * [this->size];

	this->getAllArray(out, UPWARD, this->root);

	return out;
}


template <class T>
typename BinaryTree<T>::node** BinaryTree<T>::getAllDescending()
{
	node** out = new node * [this->size];

	this->getAllArray(out, DOWNWARD, this->root);

	return out;
}

template <class T>
int BinaryTree<T>::getAllArray(node** arr, bool ascending, node* temp, int i)
{
	// get past to get the difference between the two to return
	int past = i;
	if (temp == nullptr)
	{
		return 1;
	}
	if (ascending)
	{
		i += getAllArray(arr, ascending, temp->left, i);
		arr[i - 1] = temp;
		i += getAllArray(arr, ascending, temp->right, i);
	}
	else
	{
		i += getAllArray(arr, ascending, temp->right, i);
		arr[i - 1] = temp;
		i += getAllArray(arr, ascending, temp->left, i);
	}
	return i - past;
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
	if (nnode != nullptr) {
		emptyTree(nnode->right);
		emptyTree(nnode->left);
		delete nnode;
	}
}
//reference: https://gist.github.com/toboqus/7a7b3d334c9ac59f3d5a
template <class T>
typename BinaryTree<T>::node* BinaryTree<T>::remove(T value) {

	if (this->root == nullptr) return nullptr;
	node* parent = nullptr;
	node* temp = this->root;
	while (temp != nullptr)
	{
		COUNT_BINARY
			if (value > temp->data)
			{
				parent = temp;
				temp = temp->right;
			}
			else if (value < temp->data)
			{
				parent = temp;
				temp = temp->left;
			}
			else if (temp->data == value)
			{
				break;
			}
	}

	if (temp == nullptr) return nullptr;
	if (temp->data != value) return nullptr;

	// Everything else will handle if node is a root
	// Now we need to recursively move the node down

	int left = left_height(temp);
	int right = right_height(temp);

	// If both heights are 0 then it is a leaf and can
	// be removed directly
	if (left == 1 && right == 1)
	{
		if (parent->right == temp)
		{
			parent->right = nullptr;
		}
		else
		{
			parent->left = nullptr;
		}
	}
	
	else if (right >= left)
	{
		node* t = rotate_right(temp, parent);
		if(t->right == temp) t->right = nullptr;
		t->left = temp->left;
	}
	else
	{
		node* t = rotate_left(temp, parent);
		if(t->left == temp) t->left = nullptr;
		t->right = temp->right;
	}




	if (this->check_now)
	{
		recursively_balance();
		this->check_now = false;
	}
	else
	{
		this->check_now = false;
	}
	return temp;

}

// This will iterate the tree so that there can be a new iteration of the pivots
template <class T>
void BinaryTree<T>::iterate(bool right, BinaryTree<T>::node* pivot, BinaryTree<T>::node* parent, BinaryTree<T>::node* gparent)
{
	gparent = parent;
	parent = pivot;
	if (right)
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

	if (left > right) return right;
	return left;
}

template <class T>
int BinaryTree<T>::left_height(node* in)
{
	if (in->left == nullptr) return 1;

	return 1 + left_height(in->left);
}

template <class T>
int BinaryTree<T>::right_height(node* in)
{
	if (in->right == nullptr) return 1;

	return 1 + right_height(in->right);
}

template <class T>
bool BinaryTree<T>::is_balanced(int left, int right)
{
	// get the abs of the difference
	int diff = left - right;
	if (diff < 0) diff = diff * -1;

	// Return if the difference between the two sizes is bigger than 2
	return diff <= 2;
}

template <class T>
bool BinaryTree<T>::is_balanced(node* in)
{
	return is_balanced(left_height(in), right_height(in));
}

template <class T>
void BinaryTree<T>::recursively_balance(node* parent, node* gparent)
{
	// Need a series of checks to figure out how to handle the rotation
	// Checks first to handle which level it is currently at
	if (parent == nullptr)
	{
		parent = root;
	}

	int right;
	int left;
	// First Traverse the array in both directions, if possible
	if (parent->left != nullptr)
	{
		node* nparent = parent->left;
		this->recursively_balance(nparent, parent);
		left = left_height(parent);
	}
	else
	{
		left = 1;
	}
	// Traverse to the right if applicable
	if (parent->right != nullptr)
	{
		node* nparent = parent->right;
		this->recursively_balance(nparent, parent);
		right = right_height(parent);
	}
	else
	{
		right = 1;
	}

	// After recursively traveling to the bottom we recursively move up
	if (is_balanced(left, right))
	{
		return;
	}
	else
	{
		// It is not banaced, now what to do
		// First do we need to assume rotating by root
		if (right > left)
		{
			rotate_right(parent, gparent);
		}
		else
		{
			rotate_left(parent, gparent);
		}
	}

}
template <class T>
typename BinaryTree<T>::node* BinaryTree<T>::rotate_right(node* parent, node* gparent)
{
	// Pivot will be to the right of the parent
	// Check if gparent is null, if so we can only be at the root
	if ((gparent) == nullptr)
	{
		// we need to be able to replace the right to the front
		// t will have the memory address of that direct pointer
		node* t = ((parent)->right);

		// root is now the pointer which pointers to the value that had been
		// the parent right
		root = t;
		// now we move parent down to the rightmost left
		if (t->left == nullptr)
		{
			t->left = parent;
			parent->right = nullptr;
		}
		else
		{
			t = t->left;
			while (t->right != nullptr)
			{
				t = t->right;
			}
			t->right = parent;
			parent->right = nullptr;
		}
		return t;
	}
	else
	{
		// we need to be able to replace the right to the front
		// t will have the memory address of that direct pointer
		node* t = parent->right;
		// root is now the pointer which pointers to the value that had been
		// the parent right

		// which point is actually gparent wanting to point too
		if (gparent->right == parent)
		{
			gparent->right = t;
		}
		else
		{
			gparent->left = t;
		}
		// now we move parent down to the rightmost left
		if (t->left == nullptr)
		{
			t->left = parent;
			parent->right = nullptr;
		}
		else
		{
			t = t->left;
			while (t->right != nullptr)
			{
				t = t->right;
			}
			t->right = parent;
			parent->right = nullptr;
		}
		return t;
	}
}
template <class T>
typename BinaryTree<T>::node* BinaryTree<T>::rotate_left(node* parent, node* gparent)
{

	// Pivot will be to the right of the parent
	// Check if gparent is null, if so we can only be at the root
	if (gparent == nullptr)
	{
		// we need to be able to replace the right to the front
		// t will have the memory address of that direct pointer
		node* t = parent->left;
		// root is now the pointer which pointers to the value that had been
		// the parent right
		root = t;
		// now we move parent down to the leftmost right
		if (t->right == nullptr)
		{
			t->right = parent;
			parent->left = nullptr;
		}
		else
		{
			t = t->right;
			while (t->left != nullptr)
			{
				t = t->left;
			}
			t->left = parent;
			parent->left = nullptr;
		}
		return t;
	}
	else
	{
		// we need to be able to replace the right to the front
		// t will have the memory address of that direct pointer
		node* t = parent->left;
		// root is now the pointer which pointers to the value that had been
		// the parent right

		// which point is actually gparent wanting to point too
		if (gparent->right == parent)
		{
			gparent->right = t;
		}
		else
		{
			gparent->left = t;
		}
		// now we move parent down to the leftmost right
		if (t->right == nullptr)
		{
			t->right = parent;
			parent->left = nullptr;
		}
		else
		{
			t = t->right;
			while (t->left != nullptr)
			{
				t = t->left;
			}
			t->left = parent;
			parent->left = nullptr;
		}
		return t;
	}
}
