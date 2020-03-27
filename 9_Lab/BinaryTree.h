#pragma once

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#inclde "node.h"


using namespace std

template <class T>
class BinaryTree {

	struct node {
		T data;
		struct node* right;
		struct node* left;
	};

public:
	BinaryTree() {
		root = nullptr;
	};

	~BinaryTree();

	void insert(T data);
	node* find();
	int size();
	node* getAllAscending();
	node* getAllDescending();
	void emptyTree();
	void remove(T data);



private:
	node* root;
	int height;








};







#endif
