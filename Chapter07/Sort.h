#ifndef DS_CH07_SORT_H
#define DS_CH07_SORT_H

#include <vector>

//插入排序
template <typename T>
void insertionSort(vector<T> &a)
{
    int j = 0;
    T tmp;

    for (int p = 1; p < a.size() ; ++p) {
        tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}

//希尔排序 使用Shell增量
template <typename T>
void shellSort(vector<T> &a)
{
    int i = 0, j = 0;
    T tmp;

    for (int gap = static_cast<int>(a.size() >> 1); gap > 0; gap >>= 1) {
        for (i = gap; i < a.size(); ++i) {
            tmp = a[i];
            for (j = i; j >= gap && tmp < a[j - gap]; j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = tmp;
    	}
    }
}

//堆排序 不使用附加数组
inline int leftChild(int i)
{
    return (i << 1) + 1;
}

template <typename T>
void percolateDown(vector<T> &a, int hole, int n)
{
    int child = 0;
    T tmp;
    for (tmp = a[hole]; leftChild(hole) < n; hole = child) {
        child = leftChild(hole);
        //下面if里的第一个判断保证最后一个节点是左儿子的情况下的正确性
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

template <typename T>
void heapSort(vector<T> &a)
{
    //buildheap
    for (int i = static_cast<int>(a.size() >> 1); i >= 0; --i)
        percolateDown(a, i, static_cast<int>(a.size()));

    //deleteMax
    for (int i = static_cast<int>(a.size() - 1); i > 0; --i) {
        swap(a[0], a[i]);
        percolateDown(a, 0, i);
    }
}

//归并排序 递归实现
template <typename T>
void merge(vector<T> &a, vector<T> &tmp, int leftPos, int rightPos, int rightEnd)
{
    //进入这里的时候，A,B均已排序
    //A的范围[leftPos, leftEnd], B的范围[rightPos, rightEnd]
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    //A,B里的小者放入C 相关下标推进
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos])
            tmp[tmpPos++] = a[leftPos++];
        else
            tmp[tmpPos++] = a[rightPos++];
    }

    while (leftPos <= leftEnd) //拷贝左半边
        tmp[tmpPos++] = a[leftPos++];

    while (rightPos <= rightEnd) //或者拷贝右半边
        tmp[tmpPos++] = a[rightPos++];

    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = tmp[rightEnd]; //拷贝回去
}

template <typename T>
void mergeSort(vector<T> &a, vector<T> &tmp, int left, int right)
{
    if (left < right) {
        int center = (left + right) >> 1;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        merge(a, tmp, left, center + 1, right);
    }
}

template <typename T>
void mergeSort(vector<T> &a)
{
    vector<T> tmp(a.size());
    mergeSort(a, tmp, 0, static_cast<int>(a.size() - 1));
}

#endif // DS_CH07_SORT_H
