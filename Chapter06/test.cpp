#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "BinaryHeap.h"

int main()
{
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, 100);

    int arr[100] = { 0 };
    for (int i = 0; i < 100; ++i)
        arr[i] = u(e);

    BinaryHeap<int> BHeap(100);
    for (int i = 0; i < 100; ++i)
        BHeap.insert(arr[i]);

    cout << "BHeap size: " << BHeap.size() << ", min: " << BHeap.findMin() << endl;

    getchar();
    return 0;
}
