#include "rbtree.h"

int main()
{
	RBTree rbtree;
	rbtree.Put(12, "A");
	rbtree.Put(34, "B");
	std::cout << rbtree.GetCount() << std::endl;
    std::cout << rbtree.Get(12);
}