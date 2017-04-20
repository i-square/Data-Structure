#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "BinaryHeap.h"
#include "LeftistHeap.h"
#include "BinomialQueue.h"

int main()
{
    const int maxSize = 13;
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, maxSize);

    int arr[maxSize] = { 0 };
    for (int i = 0; i < maxSize; ++i)
        arr[i] = u(e);

    BinaryHeap<int> BHeap(maxSize);
    LeftistHeap<int> LHeap;
    BinomialQueue<int> BQ;

    for (int i = 0; i < maxSize; ++i) {
        BHeap.insert(arr[i]);
        LHeap.insert(arr[i]);
        BQ.insert(arr[i]);
    }

    cout << "BHeap size: " << BHeap.size() << ", min: " << BHeap.findMin() << endl;
    cout << "LHeap min: " << LHeap.findMin() << endl;
    cout << "BQ min: " << BQ.findMin() << endl;
    cout << "LHeap:" << endl;
    LHeap.printTree();
    cout << endl << "BinomialQueue:" << endl;
    BQ.printForest();
    BQ.deleteMin();
    cout << "deleteMin:" << endl;
    BQ.printForest();

    getchar();
    return 0;
}
