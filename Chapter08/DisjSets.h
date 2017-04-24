#ifndef DS_CH08_DISJSETS_H
#define DS_CH08_DISJSETS_H

#include <vector>

class DisjSets {
public:
    explicit DisjSets(int numElements) : s(numElements, -1) {}

    int find(int x) const
    {
        if (s[x] < 0)
            return x;
        else
            return find(s[x]);
    }
    //路径压缩
    int find(int x)
    {
        if (s[x] < 0)
            return x;
        else
            return s[x] = find(s[x]);
    }
    //按高度求并 初始为-1，存储高度-1
    void unionSets(int root1, int root2)
    {
        if (s[root2] < s[root1])
            s[root1] = root2;
        else {
            if (s[root1] == s[root2])
                --s[root1]; //更新高度
            s[root2] = root1;
        }
    }

private:
    std::vector<int> s;
};

#endif // DS_CH08_DISJSETS_H
