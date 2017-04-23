#ifndef DS_CH05_HASHTABLE_OAH_H
#define DS_CH05_HASHTABLE_OAH_H

#include <vector>
#include <xhash>

//平方探测
template <typename T>
class HashTable_OAH {
    enum EntryType { ACTIVE, EMPTY, DELETED };

    int primes[24] = {
        53, 97, 193, 389, 769, 1453, 3079, 6151, 12893, 24593, 49157, 98317,
        196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
        25165843, 50331653, 100663319, 201326611, -1
    };

    int nextPrime(int n)
    {
        for (int i = 0; i < 24; ++i)
            if (n < primes[i])
                return primes[i];
        return primes[23];
    }

private:
    struct HashEntry {
        HashEntry(const T &e = T(), EntryType i = EMPTY) : ele(e), info(i) {}
        T ele;
        EntryType info;
    };

public:
    HashTable_OAH() = delete;
    explicit HashTable_OAH(int size) : curSize(0), arr(size) { makeEmpty(); }
    HashTable_OAH(const HashTable_OAH &rhs) { operator=(rhs); }
    ~HashTable_OAH() = default;
    HashTable_OAH &operator=(const HashTable_OAH &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            for (const auto HE : rhs.arr) {
                insert(HE);
            }
        }
        return *this;
    }

    int size() const { return curSize; }
    bool contains(const T &x) const
    {
        return isActive(findPos(x));
    }
    bool insert(const T &x)
    {
        int curPos = findPos(x);
        if (isActive(curPos))
            return false;

        arr[curPos] = HashEntry(x, ACTIVE);

        if (++curSize > (arr.size() >> 1))
            rehash();

        return true;
    }
    bool remove(const T &x)
    {
        int curPos = findPos(x);
        if (!isActive(curPos))
            return false;

        arr[curPos].info = DELETED;
        --curSize;
        return true;
    }

    void makeEmpty()
    {
        curSize = 0;
        for (auto &HE : arr) {
            HE.info = EMPTY;
        }
    }

private:
    bool isActive(int curPos) const
    {
        return arr[curPos].info == ACTIVE;
    }
    int findPos(const T &x) const
    {
        int offset = 1;
        int curPos = myHash(x);

        while (arr[curPos].info != EMPTY &&
            arr[curPos].ele != x) {
            //平方探测的快速方法
            //由 f(i) = f(i-1) + 2i - 1 推得
            curPos += offset;
            offset += 2;
            if (curPos >= arr.size())
                curPos -= int(arr.size());
        }

        return curPos;
    }
    void rehash()
    {
        auto oldArr = arr;
        arr.resize(nextPrime(int(oldArr.size() << 1)));
        for (auto HE : arr)
            HE.info = EMPTY;

        curSize = 0;
        for (const auto HE : oldArr)
            if (HE.info == ACTIVE)
                insert(HE.ele);
    }
    int myHash(const T &x) const
    {
        int hashVal = int(hash_value(x));
        hashVal %= arr.size();
        if (hashVal < 0)
            hashVal += int(arr.size());
        return hashVal;
    }
private:
    vector<HashEntry> arr;
    int curSize;
};

#endif // DS_CH05_HASHTABLE_OAH_H
