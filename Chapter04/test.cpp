#include <iostream>
using namespace std;

#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> BSTree;
    int a[20] = { 29, 14, 15, 84, 65, 85, 92, 81, 51, 13, 5, 18, -64, 89, 66, 21, 32, 27, 24, 52 };
    for (int i = 0; i < 20; ++i)
        BSTree.insert(a[i]);

    cout << "max: " << BSTree.findMax() << endl;
    cout << "min: " << BSTree.findMin() << endl;
    cout << boolalpha << BSTree.contains(85) << endl;
    BSTree.printTree();
    
    return 0;
}