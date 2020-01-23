#pragma once

#ifndef RB_TREE_H_
#define RB_TREE_H_

#include <iostream>
#include <algorithm>
#include <string>
#define RED 0
#define BLACK 1

class RBTree
{
private:
	struct Node {
		int key;
		std::string value;
		bool color;
		Node *left, *right, *p;
		Node(const int &_key, const std::string &_value, const bool &c = RED, Node* l = nullptr, Node* r = nullptr, Node* _p = nullptr)
			:key(_key), value(_value), color(c), left(l), right(r), p(_p) {}
	};

	uint64_t count_;

	void Clear();
	void LeftRotate(Node *x);
	void RightRotate(Node *x);
	Node* FindPutNode(Node *&p, Node *&r, const int &v);
	
	Node* FindNode(Node *r, const int &v);
	Node* FindSuccessor(Node *z);
	void RemoveFixUp(Node *x);

public:
	//×ó<¸ù<ÓÒ
	Node* root_;
	Node* nil_;

	RBTree();
	virtual ~RBTree();

	void Clear(Node *pNode);
	void Put(const int &key, const std::string &value);
	std::string Get(const int &key);
	void Remove(const int key);
	uint64_t GetCount();
	void Show();
	void Show(Node *r);

};
#endif