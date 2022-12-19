#include "ITree.h"

template <class Key>
class CartTree : public ITree<Key> {

    struct Node {
        Key value;
        int priority = 0;
        Node * left = nullptr;
        Node * right = nullptr;
        Node * parent = nullptr;
        Node(Key val) {value = val, priority=rand();} 
    };

    typedef pair<Node*, Node*> Pair;

    Pair split(Node * node, Key val) {
        if (!node) { 
            return Pair(nullptr, nullptr);
        }
        else if (node->value <= val) {
            Pair q = split(node->right, val); 
            node->right = q.first;
            return Pair(node, q.second);
        }
        else {
            Pair q = split(node->left, val);
            node->left = q.second;
            return Pair(q.first, node);
        } 
    }

    Node * merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    Node * root = nullptr; 

    public:
    void insert(Key value) {
        Pair q = split(root, value);
        Node *t = new Node(value);
        root = merge(q.first, merge(t, q.second));
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

    void erase(Key value) {
        root = eraseInternal(root, value);
    }

    Node * eraseInternal(Node * node, Key val) {
        if (!node) return nullptr;
        if (node->value == val) {
            Node * t = merge(node->left, node->right);
            delete node;
            node = t;
        }
        else {
            if (node->value < val) node->right = eraseInternal(node->right, val);
            else node->left = eraseInternal(node->left, val);
        }
        return node;
    }    
};

// int main() {
//     CartTree <int> tree;
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