#ifndef EXAMPLE_H
#define EXAMPLE_H

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

#endif // EXAMPLE_H
