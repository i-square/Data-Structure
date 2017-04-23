#include <iostream>

#include "exercise02.h"

using namespace std;

int main()
{
    maxInfo i;
    vector<int> arr;
    int temp = 0;
    cout << "Please input some numbers: ";
    while (cin >> temp) {
        arr.push_back(temp);
    }

    cout << "最小连续子序列和: " << minSubSum(arr) << endl;
    
    i = maxSubSum(arr);
    cout << "最大连续子序列和: " << i.Sum << ", 起始下标: " << i.begin << ", 结束下标: " << i.end << endl;
     
    return 0;
}