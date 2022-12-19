#include "ITree.h"

enum NodeColor {Black, Red};

template<class Key>
struct Node {
        Key key;
        NodeColor color;
        Node <Key> * left;
        Node <Key> * right;
        Node <Key> * parent;
        Node <Key>(Key k, NodeColor c, Node <Key>* p, Node <Key>*l, Node <Key>*r) :
            key(k), color(c), parent(p), left(l), right(r) { };
    };

template<class Key>
class RBTree : public ITree<Key> {
public:
	RBTree();
	~RBTree();

	void insert(Key value);    
	void erase(Key value); 
	bool find(Key value);

	void leftRotate(Node <Key>* &root, Node <Key>* x);
	void rightRotate(Node <Key>* &root, Node <Key>* y);
	
	void insertInternal(Node <Key>* &root, Node <Key>* node);
	void insertFixUp(Node <Key>* &root, Node <Key>* node);
	void destroy(Node <Key>* &node);

	void remove(Node <Key>*& root, Node <Key>*node);
	void removeFixUp(Node <Key>* &root, Node <Key>* node, Node <Key>*parent);

	Node <Key> * search(Node <Key>*node, Key key);

private:
	Node <Key> * root;
};

template<class Key>		
RBTree<Key>::RBTree() : root(nullptr) {}

template<class Key>		
RBTree<Key>::~RBTree() {
	destroy(root);
}

template<class Key>
void RBTree<Key>::leftRotate(Node <Key> * &root, Node <Key> * x) {
	Node <Key>*y = x->right;
	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;

	y->parent = x->parent;
	if (x->parent == nullptr)
		root = y;
	else {
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
};

template<class Key>		
void RBTree<Key>::rightRotate(Node <Key>*&root, Node <Key>*y) {
	Node <Key>*x = y->left;
	if (x) y->left = x->right;
	else y->left = nullptr;
	if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == nullptr)
		root = x;
	else {
		if  (y == y->parent->right)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
};

template<class Key>
void RBTree<Key>::insert(Key value) {
	Node <Key>*z = new Node <Key>(value, Red, nullptr, nullptr, nullptr);
	insertInternal(root, z);
};

template<class Key>
void RBTree<Key>::insertInternal(Node <Key>* &root, Node <Key>* node) {
	Node <Key> *x = root;
	Node <Key> *y = nullptr;
	while (x != nullptr) {
		y = x;
		if (node->key > x->key)
			x = x->right;
		else
			x = x->left;
	}
	node->parent = y;
	if(y != nullptr) {
		if (node->key > y->key)
			y->right = node;
		else
			y->left = node;
	}
	else 
		root = node;
	node->color = Red;
	insertFixUp(root, node);
};

template<class Key>
void RBTree<Key>::insertFixUp(Node <Key>* &root, Node <Key>* node) {
	Node <Key>*parent;
	parent = node->parent;
	while (node != RBTree::root  && parent->color == Red) {
		Node <Key>*gparent = parent->parent;
		if (gparent->left == parent) {
			Node <Key>*uncle = gparent->right;
			if (uncle != nullptr && uncle->color == Red) {
				parent->color = Black;
				uncle->color = Black;
				gparent->color = Red;
				node = gparent;
				parent = node->parent;
			}
			else {
				if (parent->right == node) {
					leftRotate(root, parent);
					swap(node, parent);
				}
				rightRotate(root, gparent);
				gparent->color = Red;
				parent->color = Black;
				break;
			}
		}
		else {
			Node <Key>*uncle = gparent->left;
			if (uncle != nullptr && uncle->color == Red) {
				gparent->color = Red;
				parent->color = Black;
				uncle->color = Black;

				node = gparent;
				parent = node->parent;
			}
			else {
				if (parent->left == node)
				{
					rightRotate(root, parent);
					swap(parent, node);
				}
				leftRotate(root, gparent);
				parent->color = Black;
				gparent->color = Red;
				break;
			}
		}
	}
	root->color = Black;
}

template<class Key>
void RBTree<Key>::destroy(Node <Key>* &node) {
	if (node == nullptr)
		return;
	destroy(node->left);
	destroy(node->right);
	delete node;
	node = nullptr;
}

template<class Key>
void RBTree<Key>::erase(Key value) {
	Node <Key>*deletenode = search(root, value);
	if (deletenode != nullptr)
		remove(root, deletenode);
}

template<class Key>
void RBTree<Key>::remove(Node <Key>*&root, Node <Key>*node) {
	Node <Key> *child, *parent;
	NodeColor color;

	if (node->left != nullptr && node->right != nullptr) {
		Node <Key> *replace = node;
		replace = node->right;
		while (replace->left != nullptr) {
			replace = replace->left;
		}

		if (node->parent != nullptr) {
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
			root = replace;
		
		child = replace->right;
		parent = replace->parent;
		color = replace->color;
		
		if (parent == node)
			parent = replace;
		else {
			if (child != nullptr)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != nullptr)    
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child) {
		child->parent = parent;
	}

	if (parent) {
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	
	else
		RBTree::root = child;		

	if (color == Black) {
		removeFixUp(root, child, parent);
	}
	delete node;
}

template<class Key>
void RBTree<Key>::removeFixUp(Node <Key>* &root, Node <Key>* node,Node <Key>*parent) {
	Node <Key>*othernode;
	while (((!node) || node->color == Black) && node != RBTree::root) {
		if (parent->left == node) {
			othernode = parent->right;
			if (othernode->color == Red) {
				othernode->color = Black;
				parent->color = Red;
				leftRotate(root, parent);
				othernode = parent->right;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black)) {
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else {
				if (!(othernode->right) || othernode->right->color == Black) {
					othernode->left->color=Black;
					othernode->color = Red;
					rightRotate(root, othernode);
					othernode = parent->right;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->right->color = Black;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else {
			othernode = parent->left;
			if (othernode->color == Red) {
				othernode->color = Black;
				parent->color = Red;
				rightRotate(root, parent);
				othernode = parent->left;
			}
			if ((!othernode->left || othernode->left->color == Black) && (!othernode->right || othernode->right->color == Black)) {
				othernode->color = Red;
				node = parent;
				parent = node->parent;
			}
			else {
				if (!(othernode->left) || othernode->left->color == Black) {
					othernode->right->color = Black;
					othernode->color = Red;
					leftRotate(root, othernode);
					othernode = parent->left;
				}
				othernode->color = parent->color;
				parent->color = Black;
				othernode->left->color = Black;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if (node)
		node->color = Black;
}

template<class Key>
Node <Key> * RBTree<Key>::search(Node <Key>*node, Key key) {
	if (node == nullptr || node->key == key)
		return node;
	else
		if (key > node->key)
			return search(node->right, key);
		else
			return search(node->left, key);
}

template<class Key>
bool RBTree<Key>::find(Key value) {
	Node <Key> * node = search(root, value);
	return node && node->key == value;
}

// int main() {
//     RBTree <int> tree;
//     // tree.insert(1);
// 	tree.insert(1);
//     tree.insert(2);
// 	tree.insert(3);
//     tree.insert(4);
//     tree.insert(5);
// 	tree.insert(6);
// 	tree.insert(7);
// 	tree.insert(8);
//     tree.insert(9);
//     tree.insert(10);
//     int k = 0;
//     cin >> k;
//     cout << tree.find(k) << endl;

// 	for (int i = 0; i <= 10; ++i) {
// 		tree.erase(i);
// 	}

// 	for (int i = 0; i <= 10; ++i) {
// 		cout << tree.find(i) << " ";
// 	}
    
//     return 0;
// }
