#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
#include <sstream>
using namespace std;

template <class Key>
struct ITree {
    public:
    virtual void insert(Key value) = 0;
    virtual bool find(Key value) = 0;
    virtual void erase(Key value) = 0;
};
