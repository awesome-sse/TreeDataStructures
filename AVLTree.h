#include "ITree.h"

template <class T>
struct DefaultComparator {
    int operator() (const T& l, const T& r) const {
        if (l < r) return -1;
        if (l > r) return 1;
        return 0;
    }
};

template <class Key, class Comparator = DefaultComparator<Key>>
class AvlTree : public ITree<Key> {
    struct Node {
        Node *left;
        Node *right;
        Key key;
        uint8_t height;
        int n_elems;
        Node(const Key& key) : left(nullptr), right(nullptr), key(key), height(1), n_elems(1) {}
        ~Node() {}
    };

public:
    
    AvlTree(Comparator comp = Comparator()) : root(nullptr), comp(comp) {}
    ~AvlTree() {
        destroyTree(root);
    }

    bool find(Key key) {
        return hasInternal(key, root);
    }

    void insert(Key key) {
        root = insertInternal(key, root);
    }

    void erase(Key key) {
        root = eraseInternal(key, root);
    }

private:
    void destroyTree(Node * node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    bool hasInternal(Key key, Node* node) {
        if (!node) return false;
        int cmp_res = comp(key, node->key);
        if (cmp_res == 0) return true;
        else if (cmp_res == -1) return hasInternal(key, node->left);
        else return hasInternal(key, node->right);
    }

    Node* insertInternal(Key key, Node* node) {
        if( !node ) return new Node(key);

        int cmp_res = comp(key, node->key);
        if(cmp_res == -1)
            node->left = insertInternal(key, node->left);
        else
            node->right = insertInternal(key, node->right);
        return balance(node);
    }

    Node *eraseInternal(Key key, Node *node) {
        if (!node) return nullptr;
        int cmp_res = comp(key, node->key);
        if (cmp_res == -1) node->left = eraseInternal(key, node->left);
        else if (cmp_res == 1) node->right = eraseInternal(key, node->right);
        else {
            Node *left = node->left;
            Node *right = node->right;

            delete node; 

            if (!right) return left;
            Node *min_node = find_and_remove_min(right);
            if (!min_node) {
                min_node = right;
            }
            else min_node->right = right;
            min_node->left = left;

            return balance(min_node);
        }
        return balance(node);
    }

    Node* find_min(Node *node) {
        if (!node->left) return node;
        return find_min(node->left);
    }

    Node* remove_min(Node* node) {
        if(!node->left)
            return node->right;
        node->left = remove_min(node->left);
        return balance(node);
    }

    Node* find_and_remove_min(Node* node) {
        if(!node->left) return nullptr;
        
        Node* tmp = find_and_remove_min(node->left); 
        
        if (!tmp) {
            Node* left = node->left;
            node->left = node->left->right;
            balance(node);
            return left;
        }
        else {
            balance(node);
            return tmp;
        }
    }

    uint8_t height(Node *node) {
        if (!node) return 0;
        return node->height;
    }

    int elems(Node *node) {
        if (!node) return 0;
        return node->n_elems;
    }

    uint8_t bfactor(Node *node) {
        return height(node->right) - height(node->left);
    }

    void fix_height(Node* node) {
        uint8_t hl = height(node->left);
        uint8_t hr = height(node->right);
        node->height = (hl>hr?hl:hr)+1;
    }

    void fix_n_elems(Node* node) {
        int elems_l = elems(node->left);
        int elems_r = elems(node->right);
        node->n_elems = elems_l + elems_r + 1;
    }

    Node* rotate_left(Node* node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fix_height(node);
        fix_height(tmp);
        fix_n_elems(node);
        fix_n_elems(tmp);
        return tmp;
    }
    
    Node* rotate_right(Node* node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fix_height(node);
        fix_height(tmp);
        fix_n_elems(node);
        fix_n_elems(tmp);
        return tmp;
    }   

    Node *balance(Node * node) {
        fix_height(node);
        fix_n_elems(node);
        if( bfactor(node) == 2)
        {
            if(bfactor(node->right) < 0 )
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        if( bfactor(node) == -2)
        {
            if(bfactor(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node; 
    }

    Node *root;
    Comparator comp;
};


// int main() {
//     AvlTree <int> avltree;
//     avltree.insert(1);
//     avltree.insert(2);
//     avltree.insert(4);
//     avltree.insert(3);
//     avltree.insert(0);
//     avltree.insert(1);
//     int k = 0;
//     cin >> k;
//     cout << avltree.find(k) << endl;
//     avltree.erase(k);
//     cout << avltree.find(k) << endl;
//     return 0;
// }