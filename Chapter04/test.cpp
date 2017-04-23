#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "exercise04.h"

int main()
{
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(-50, 50);

    int arr[50] = { 0 };
    for (int i = 0; i < 50; ++i)
        arr[i] = u(e);

    cout << "BinarySearchTree Test:" << endl;
    BinarySearchTree<int> BSTree;
    for (int i = 0; i < 20; ++i)
        BSTree.insert(arr[i]);

    cout << "max: " << BSTree.findMax() << endl;
    cout << "min: " << BSTree.findMin() << endl;
    cout << "是否包含5 ? " << boolalpha << BSTree.contains(5) << endl;
    BSTree.printTree();
    cout << endl << endl << endl;

    cout << "AVLTree Test:" << endl;
    AVLTree<int> AvlTree;

    for (int i = 0; i < 30; ++i)
        AvlTree.insert(arr[i+20]);

    AvlTree.printTree();

    cout << endl << "Remove ";
    for (int i = 0; i < 5; ++i) {
        int t = arr[i + 20 + 4 * i];
        cout << t << ",";
        AvlTree.remove(t);
    }
    cout << endl << endl;
    
    AvlTree.printTree();

    //ex4.11
    Set<int> st;
    for (int i = 0; i < 50; ++i)
        st.insert(arr[i]);

    cout << "Set contains: " << endl;
    Set<int>::const_iterator itr = st.begin();
    for (int i = 0; i < st.size(); ++i, ++itr) {
        cout << *itr << ",";
    }
    cout << endl;
    cout << "erase: " << arr[10] << endl;
    st.erase(arr[10]);
    cout << "Now contains: " << endl;
    itr = st.begin();
    for (int i = 0; i < st.size(); ++i, ++itr) {
        cout << *itr << ",";
    }
    cout << endl;

    getchar();
    return 0;
}