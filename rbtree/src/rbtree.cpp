#include "rbtree.h"

RBTree::RBTree() {
    nil_ = new Node(-1, "", BLACK, nil_, nil_, nil_);
    root_ = nil_;
    count_ = 0;
}

RBTree::~RBTree() {
    Clear();
    delete nil_;
}

void RBTree::Clear() {
    Clear(root_);
    root_ = nil_;
}

void RBTree::Clear(Node* pNode)
{
    if (pNode == nil_) {
        return;
    }

    Clear(pNode->left);
    Clear(pNode->right);
    delete pNode;
}

void RBTree::LeftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nil_) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == nil_) {
        root_ = y;
    }
    else if (x->p->left == x) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    x->p = y;
    y->left = x;
}

void RBTree::RightRotate(Node* x)
{
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nil_) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == nil_) {
        root_ = y;
    }
    else if (x->p->left == x) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    x->p = y;
    y->right = x;
}

RBTree::Node* RBTree::FindPutNode(Node*& p, Node*& r, const int& v) {
    if (r == nil_) {
        r = new Node(v, "", RED, nil_, nil_, p);
        if (p == nil_) {
            root_ = r;
        }
        if (v < p->key) {
            p->left = r;
        }
        else {
            p->right = r;
        }

    }
    else {
        if (v < r->key) {
            return FindPutNode(r, r->left, v);
        }
        else {
            return FindPutNode(r, r->right, v);
        }
    }
    return r;
}

void RBTree::Put(const int& key, const std::string& value) {
    Node* z = FindPutNode(nil_, root_, key);
    z->value = value;
    count_++;
    while (z->p->color == RED) {
        if (z->p->p->left == z->p) {
            if (z->p->p->right->color == RED) {
                z->p->color = BLACK;
                z->p->p->right->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z->p->right == z) {
                    z = z->p;
                    LeftRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(z->p->p);
            }
        }
        else {
            if (z->p->p->left->color == RED) {
                z->p->color = BLACK;
                z->p->p->left->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z->p->left == z) {
                    z = z->p;
                    RightRotate(z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(z->p->p);
            }
        }
    }
    root_->color = BLACK;
}

std::string RBTree::Get(const int& key) {
    Node* result;
    return FindNode(root_, key)->value;
}

uint64_t RBTree::GetCount()
{
    return count_;
}

RBTree::Node* RBTree::FindNode(Node* r, const int& v) {
    if (root_ == nil_) return nil_;
    if (r == nil_) return nil_;
    if (v == r->key) return r;
    else if (v > r->key) {
        return FindNode(r->right, v);
    }
    else {
        return FindNode(r->left, v);
    }
}

RBTree::Node* RBTree::FindSuccessor(Node* z) {
    while (z->left != nil_) {
        z = z->left;
    }
    return z;
}

void RBTree::RemoveFixUp(Node* x) {
    while (x != root_ && x->color == BLACK) {
        if (x->p->left == x) {
            Node* bro = x->p->right;
            if (bro->color == RED) {
                //cout<<"case:1"<<endl;
                bro->color = BLACK;
                bro->p->color = RED;
                LeftRotate(x->p);
                bro = x->p->right;
            }
            if (bro->left->color == BLACK && bro->right->color == BLACK) {
                //cout<<"case:2"<<endl;
                bro->color = RED;
                x = x->p;
            }
            else {
                if (bro->right->color == BLACK) {
                    //cout<<"case:3"<<endl;
                    bro->color = RED;
                    bro->left->color = BLACK;
                    RightRotate(bro);
                    bro = x->p->right;
                }
                //cout<<"case:4"<<endl;
                bro->color = x->p->color;
                x->p->color = BLACK;
                bro->right->color = BLACK;
                LeftRotate(x->p);
                x = root_;
            }
        }
        else {
            Node* bro = x->p->left;
            if (bro->color == RED) {
                //cout<<"case:5"<<endl;
                bro->color = BLACK;
                x->p->color = RED;
                RightRotate(x->p);
                bro = x->p->left;
            }
            if (bro->left->color == BLACK && bro->right->color == BLACK) {
                //cout<<"case:6"<<endl;
                bro->color = RED;
                x = x->p;
            }
            else {
                if (bro->left->color == BLACK) {
                    //cout<<"case:7"<<endl;
                    bro->right->color = BLACK;
                    bro->color = RED;
                    LeftRotate(bro);
                    bro = x->p->left;
                }
                //cout<<"case:8"<<endl;
                bro->color = x->p->color;
                x->p->color = BLACK;
                bro->left->color = BLACK;
                RightRotate(x->p);
                x = root_;
            }
        }
    }
    x->color = BLACK;
}

void RBTree::Remove(int key) {
    Node* z = FindNode(root_, key);
    if (z == nil_) return;

    Node* y = nil_;

    if (z->left == nil_ || z->right == nil_) {
        y = z;
    }
    else {
        y = FindSuccessor(z->right);
        //cout<<"replace node->val : "<<y->val<<endl;
        std::swap(y->key, z->key);
        std::swap(y->value, z->value);
    }

    Node* yp = y->p;
    Node* ychild = (y->left != nil_) ? y->left : y->right;
    ychild->p = yp;

    if (yp->left == y) {
        yp->left = ychild;
    }
    else {
        yp->right = ychild;
    }

    if (yp == nil_) {
        root_ = ychild;
    }

    if (y->color == BLACK) {
        RemoveFixUp(ychild);
    }
    delete y;
    count_--;
}

void RBTree::Show() {
    Show(root_);
}

void RBTree::Show(Node* r) {
    if (root_ == nil_) return;
    std::cout << r->key << ' ' << r->value << ' ' << r->color << ' ' << r->p->key << ' ' << r->left->key << ' ' << r->right->key << std::endl;
    if (r->left != nil_) {
        Show(r->left);
    }
    if (r->right != nil_) {
        Show(r->right);
    }
}
