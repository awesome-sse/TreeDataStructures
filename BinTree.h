#include "ITree.h"

template <class Key>
class BinTree : public ITree<Key> {
    private: 
    struct Node {
        Key value;
        Node * left;
        Node * right;
        Node * parent;

        Node(Key Value) : value(Value), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node * root = nullptr;

    Node * min_leaf(Node * root) {
        Node * now = root;
        while (now->left) {
            now = now->left;
        }
        return now;
    }

    Node * max_leaf(Node * root) {
        Node * now = root;
        while (now->right) {
            now = now->right;
        }
        return now;
    }

    Node * next_leaf(Node * node) {
        if (node->right) {
            return min_leaf(node->right);
        }      
        return nullptr;
    }

    Node * prev(Node * node) {
        if (node->left) {
            return max_leaf(node->left);
        }      
        return nullptr;
    }

    void erase_internal(Node * node) {
        if (!node->left and !node->right) {
            if (node->parent->left == node) {
                node->parent->left = nullptr;
            }
            else {
                node->parent->right = nullptr;
            }            
            if (root == node) root = nullptr;
        }
        else if (!node->left) {
            if (node->parent->left == node) {
                node->parent->left = node->right;
            }
            else {
                node->parent->right = node->right;
            }
            if (root == node) root = node->right;
        }
        else if (!node->right) {
            if (node->parent->left == node) {
                node->parent->left = node->left;
            }
            else {
                node->parent->right = node->left;
            }
            if (root == node) root = node->left;
        }
        else {
            Node * next = next_leaf(node);
            
            if (next == node->right) {
                next->left = node->left;
                next->parent = node->parent;
            }
            else {
                next->left = node->left;
                next->parent->left = next->right;
                next->right = node->right;
                next->parent = node->parent;
            }
            
            if (root == node) root = next;
            else {
                if (node->parent->left == node) {
                    node->parent->left = next;
                }
                else {
                    node->parent->right = next;
                }
            }
        }

        delete node;
        
        return;
    }

    public:

    void insert(Key value) {
        if (!root) {
            root = new Node(value);
            root->parent = root;
        }
        else {
            Node * now = root;
            if (value <= now->value) {
                now = root->left;
            }
            else {
                now = root->right;
            }

            Node * prev = root;

            while (now) {
                prev = now;
                if (value < now->value) {
                    now = now->left;
                }
                else {
                    now = now->right;
                }
            }
            now = new Node(value);
            if (value < prev->value) {
                prev->left = now;
            }
            else {
                prev->right = now;
            }
            now->parent = prev;
        }
    }

    void erase(Key value) {
        Node * now = root;
        while (now) {
            if (now->value == value) {
                erase_internal(now);
                break;
            }
            if (value <= now->value) {
                now = now->left;
            }
            else {
                now = now->right;
            }
        }
    }

    bool find(Key value) {
        Node * now = root;
        while (now) {
            if (now->value == value) {
                return true;
            }
            else if (value < now->value) {
                now = now->left;
            }
            else {
                now = now->right;
            }
        }
        return false;
    }
};


// int main() {
//     BinTree <int> tree;
//     tree.insert(1);
//     tree.insert(2);
//     tree.insert(4);
//     tree.insert(3);
//     tree.insert(0);
//     // tree.insert(1);
//     int k = 0;
//     cin >> k;
//     cout << tree.find(k) << endl;
//     tree.erase(k);
//     cout << tree.find(k) << endl;
//     return 0;
// }