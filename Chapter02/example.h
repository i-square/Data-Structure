#ifndef DS_CH02_EXAMPLE_H
#define DS_CH02_EXAMPLE_H

#include <vector>
using std::vector;

// 二分搜索
template <typename Comparable>
int binarySearch(const vector<Comparable> &a, const Comparable &x)
{
    int low = 0, high = a.size() - 1, mid = 0;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (a[mid] < x)
            low = mid + 1;
        else if (a[mid] > x)
            high = mid - 1;
        else
            return mid;
    }
    return -1; // -1 means NOT FOUND
}

// 最大公因数的欧几里得算法
long gcd(long m, long n)
{
    while (n != 0) {
        long rem = m % n;
        m = n;
        n = rem;
    }
    return m;
}

// 幂运算的递归算法
long pow(long x, int n)
{
    if (n == 0)
        return 1;
    if (n & 1)
        return pow(x, n - 1) * x;
    else
        return pow(x * x, n >> 1);
}

#endif // DS_CH02_EXAMPLE_H
