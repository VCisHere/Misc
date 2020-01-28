#pragma once
#ifndef BS_TREE_H_
#define BS_TREE_H_

#include <iostream>
class BSTree
{
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* p;
        Node(const int& _key, Node* l = nullptr, Node* r = nullptr, Node* _p = nullptr)
            :key(_key), left(l), right(r), p(_p) {}
    };

    uint64_t count_;

    void Clear(Node* r);
    Node* FindPutNode(Node*& p, Node*& r, const int& v);

    Node* FindNode(Node* r, const int& v);
    Node* FindSuccessor(Node* z);

public:
    Node* nil_;
    Node* root_;

    BSTree();
    virtual ~BSTree();
    void Clear();
    void Put(const int &key);
    Node* Get(const int &key);
    bool Delete(const int &key);
    uint64_t GetCount();
    void Show();
    void Show(Node* r);
};

#endif



