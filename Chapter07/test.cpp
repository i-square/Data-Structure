#include <iostream>
#include <random>

using namespace std;

#include "Timer.h"
#include "Sort.h"

#define PRINT_SORT_TIME(A, sortfun) \
{\
    vector<int> arrt(A);\
    Timer ts;\
    sortfun(arrt);\
    cout << #sortfun##" " << maxSize << " 个随机数用时: " << ts.stop_delta<Timer::ms>() << " ms" << endl;\
}

int main()
{
    const int maxSize = 10000;
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(1, maxSize);

    vector<int> arr;
    for (int i = 0; i < maxSize; ++i)
        arr.push_back(u(e));

    if (maxSize <= 1000)
        PRINT_SORT_TIME(arr, insertionSort);
    PRINT_SORT_TIME(arr, shellSort);
    PRINT_SORT_TIME(arr, heapSort);
    PRINT_SORT_TIME(arr, mergeSort);
    PRINT_SORT_TIME(arr, mergeSort2);
    PRINT_SORT_TIME(arr, quickSort);
    {
        vector<int> arr1(arr);
        quickSelect(arr1, 0, maxSize - 1, maxSize >> 1);
        cout << "the median num is: " << arr1[(maxSize >> 1) - 1] << endl;
    }

    getchar();
    return 0;
}