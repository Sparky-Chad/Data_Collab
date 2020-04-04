

template <class T>
void BinaryTree<T>::insert(T val) {
	insert(&(root), val);
}


template <class T>
void BinaryTree<T>::insert(struct node** node, T val) {

	if (*node == nullptr) {
		struct node* temp = new struct node;
		temp->data = val;
		temp->left = nullptr;
		temp->right = nullptr;
		*node = temp;

		size++;
	}
	else {
		if (val > (*node)->value) {
			insert(&(*node)->right, val);
		}
		if (val == (*node)->value) {
			throw inTreeAlready();
		}
		else {
			insert(&(*node)->left, val);
		}
	}


}


template <class T>
node* BinaryTree<T>::find(T val) {
	return find(root, val);
}

template <class T>
node* BinaryTree<T>::find(struct node* node, T val) {
	if (node == nullptr) {
		return nullptr;
	}
	else {
		if (val == node->value) {
			return node;
		}
		if (val > node->value) {
			return find(node->right, val);
		}
		else {
			return find(node->left, val);
		}
	}
}

template <class T>
int BinaryTree<T>::size() {
	return size;
}




node** BinaryTree<T>::getAllAscending() {
	
}


template <class T>
node** BinaryTree<T>::getAllDescending(){






}

//must input root to delete entire tree
template <class T>
void BinaryTree<T>::emptyTree(node* node) {
	if (node != nullptr) {
		emptyTree(node->right);
		emptyTree(node->left);
		delete node;
	}
	root->right = nullptr;
	root->left = nullptr;
}
template <class T>
void BinaryTree<T>::remove(T data) {


}

// This will iterate the tree so that there can be a new iteration of the pivots
template <class T>
void BinaryTree<T>::iterate(node* left, node* right, node* pivot, node* parent, node* gparent)
{
	left = pivot->left;
	right = pivot->right;
	gparent = parent;
	parent = pivot;
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
	// Check which side of the gparent is being rotated
	if(gparent->left == parent)
	{
		gparent->left = pivot;
	}
	else
	{
		gparent->right = pivot;
	}

	// Because we are rotating to the right we need to move the parent to the absolute
	// left of the pivot, this may unbalence tree and as such we must recursively rebalance
	// to the current pivot
	node* temp = pivot;
	while(temp->left != nullptr)
	{
		temp = temp->left; 
	}
	temp->left = parent;

	recursively_balance(pivot);
}

template <class T>
void BinaryTree<T>::rotate_left(node* pivot, node* parent, node* gparent)
{
	// Check which side of the gparent is being rotated
	if(gparent->left == parent)
	{
		gparent->left = pivot;
	}
	else
	{
		gparent->right = pivot;
	}

	// Because we are rotating to the right we need to move the parent to the absolute
	// left of the pivot, this may unbalence tree and as such we must recursively rebalance
	// to the current pivot
	node* temp = pivot;
	while(temp->right != nullptr)
	{
		temp = temp->right; 
	}
	temp->right = parent;

	recursively_balance(pivot);
}



//reference: https://gist.github.com/toboqus/7a7b3d334c9ac59f3d5a