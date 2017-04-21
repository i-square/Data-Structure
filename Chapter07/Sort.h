#ifndef DS_CH07_SORT_H
#define DS_CH07_SORT_H

#include <vector>

//≤Â»Î≈≈–Ú
template <typename T>
void insertionSort(vector<T> &a)
{
    int j = 0;
    T tmp;

    for (int p = 1; p < a.size() ; ++p) {
        tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

#endif // DS_CH07_SORT_H
