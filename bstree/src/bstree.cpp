#include "bstree.h"
BSTree::BSTree()
{
    nil_ = new Node(-1, nil_, nil_, nil_);
    root_ = nil_;
    count_ = 0;
}

BSTree::~BSTree() {
    Clear();
    delete nil_;
}

void BSTree::Clear() {
    Clear(root_);
    root_ = nil_;
}

void BSTree::Clear(Node* r)
{
    if (r == nil_) {
        return;
    }

    Clear(r->left);
    Clear(r->right);
    delete r;
}

BSTree::Node* BSTree::FindNode(Node* r, const int& _key) {
    if (r == nil_) {
        return nil_;
    }
    if (_key == r->key) {
        return r;
    }
    else if (_key > r->key) {
        return FindNode(r->right, _key);
    }
    else {
        return FindNode(r->left, _key);
    }
}

BSTree::Node* BSTree::Get(const int &_key) {
    Node* result;
    return FindNode(root_, _key);
}

BSTree::Node* BSTree::FindSuccessor(Node* z) {
    //查找后继结点
    while (z->left != nil_) {
        z = z->left;
    }
    return z;
}

bool BSTree::Delete(const int &_key) {
    Node* s = FindNode(root_, _key);
    if (s == nil_) {
        return false;
    }
    Node* y = nil_;
    if (s->left == nil_ || s->right == nil_) {
        //只有一个子节点或无子结点
        y = s;
    }
    else {
        //左右结点均存在
        y = FindSuccessor(s->right);
        s->key = y->key;
    }

    if (y->right != nil_) {
        y->right->p = y->p;
    }

    if (y->p->left == y) {
        y->p->left = y->right;
    }
    else {
        y->p->right = y->right;
    }

    if (y->p == nil_) {
        root_ = y->right;
    }
    delete(y);
    count_--;
    return true;
}

BSTree::Node* BSTree::FindPutNode(Node*& p, Node*& r, const int& _key) {
    if (r == nil_) {
        r = new Node(_key, nil_, nil_, p);
        if (p == nil_) {
            root_ = r;
        }
        if (_key < p->key) {
            p->left = r;
        }
        else {
            p->right = r;
        }
    }
    else {
        if (_key < r->key) {
            return FindPutNode(r, r->left, _key);
        }
        else {
            return FindPutNode(r, r->right, _key);
        }
    }
    return r;
}

void BSTree::Put(const int &_key) {
    Node* z = FindPutNode(nil_, root_, _key);
    z->key = _key;
    count_++;
}

void BSTree::Show() {
    Show(root_);
}

void BSTree::Show(Node* r) {
    if (root_ == nil_) return;
    std::cout << r->key << ' ' << r->p->key << ' ' << r->left->key << ' ' << r->right->key << std::endl;
    if (r->left != nil_) {
        Show(r->left);
    }
    if (r->right != nil_) {
        Show(r->right);
    }
}

uint64_t BSTree::GetCount() {
    return count_;
}