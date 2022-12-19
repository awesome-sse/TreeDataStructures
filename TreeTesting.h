#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include "AVLTree.h"
#include "BinTree.h"
#include "CartesianTree.h"
#include "RedBlackTree.h"

template <class Key>
class TreeTesting {
    public:
    double check_time(string tree_name, string func_name, vector <Key> data);
    double check_time_insert(ITree<Key> * tree, vector <Key> data);
    double check_time_find(ITree<Key> * tree, vector <Key> data);
    double check_time_erase(ITree<Key> * tree, vector <Key> data);
};

template<class Key>
double TreeTesting<Key>::check_time_insert(ITree<Key> * tree, vector <Key> data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (size_t i = 0; i < data.size(); ++i) {
        tree->insert(data[i]);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

template<class Key>
double TreeTesting<Key>::check_time_find(ITree<Key> * tree, vector <Key> data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (size_t i = 0; i < data.size(); ++i) {
        tree->find(data[i]);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

template<class Key>
double TreeTesting<Key>::check_time_erase(ITree<Key> * tree, vector <Key> data) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    for (size_t i = 0; i < data.size(); ++i) {
        tree->erase(data[i]);
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

template<class Key>
double TreeTesting<Key>::check_time(string tree_name, string func_name, vector <Key> data) {
    RBTree <Key> tree;
    if (tree_name == "AvlTree") AvlTree <Key> tree;
    else if (tree_name == "BinTree") BinTree <Key> tree;
    else if (tree_name == "CartTree") CartTree <Key> tree;

    if (func_name == "insert") return check_time_insert(&tree, data);
    if (func_name == "find") {
        check_time_insert(&tree, data);

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine rng(seed);
        shuffle(data.begin(), data.end(), rng);

        return check_time_find(&tree, data);
    }
    if (func_name == "erase") {
        check_time_insert(&tree, data);

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine rng(seed);
        shuffle(data.begin(), data.end(), rng);

        return check_time_erase(&tree, data);
    }
    return 0;

}
