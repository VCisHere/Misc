#include "bstree.h"

int main()
{
    BSTree bst;
    int a[12] = { 2, 3, 9, 8, 4, 5, 1, 7, 12, 6, 11, 13};
    for (int i = 0; i < 12; i++) bst.Put(a[i]);
    bst.Delete(9);
    bst.Show();
    bst.Clear();
}