#ifndef DS_CH02_EXERCISE02_H
#define DS_CH02_EXERCISE02_H

#include <vector>
using std::vector;

//2.17
//a.求最小连续子序列和  O(N)算法
int minSubSum(const vector<int> &a)
{
    int minSum = 0, thisSum = 0;
    for (int i = 0; i < a.size(); ++i) {
        thisSum += a[i];
        if (thisSum < minSum)
            minSum = thisSum;
        else if (thisSum > 0)
            thisSum = 0;
    }
    return minSum;
}

//2.19
//返回最大连续子序列和以及对应的下标
struct maxInfo {
    maxInfo() = default;
    int Sum;
    int begin;
    int end;
};

maxInfo info;

maxInfo maxSubSum(const vector<int> &a)
{
    int thisSum = 0;
    bool isBegin = false;
    for (int i = 0; i < a.size(); ++i) {
        thisSum += a[i];
        if (thisSum > info.Sum) {
            info.Sum = thisSum;
            if (!isBegin) {
                isBegin = true;
                info.begin = i;
            }
            info.end = i;
        } else if (thisSum < 0) {
            thisSum = 0;
            isBegin = false;
        }
    }
    return info;
}

#endif // DS_CH02_EXERCISE02_H
