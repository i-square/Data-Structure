#include <iostream>
using namespace std;

#include "DisjSets.h"

int main()
{
    DisjSets One(5000);

    int root1 = 0, root2 = 0;
    for (int i = 10; i < 1000; ++i) {
        root1 = One.find(2 * i + 1);
        root2 = One.find(3 * i + 1);
        One.unionSets(root1, root2);
    }
    for (int i = 0; i < 1000; ++i) {
        cout << i << " : " << One.find(i) << endl;
    }

    getchar();
    return 0;
}