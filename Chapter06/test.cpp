#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "BinaryHeap.h"

int main()
{
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, 10000);

    int arr[10000] = { 0 };
    for (int i = 0; i < 10000; ++i)
        arr[i] = u(e);

    BinaryHeap<int> BHeap(10000);
    for (int i = 0; i < 10000; ++i)
        BHeap.insert(arr[i]);
    BinaryHeap<int> tHeap(BHeap);

    cout << tHeap.findMin() << endl;

    getchar();
    return 0;
}
