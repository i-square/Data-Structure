#ifndef DS_CH05_HASHTABLE_SC_H
#define DS_CH05_HASHTABLE_SC_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <xhash>

template <typename T>
class HashTable_SC {
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

public:
    HashTable_SC() = delete;
    explicit HashTable_SC(int size) : curSize(0), theLists(size) { makeEmpty(); }
    HashTable_SC(const HashTable_SC &rhs) { operator=(rhs); }
    ~HashTable_SC() = default;
    HashTable_SC &operator=(const HashTable_SC &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            for (const auto l : rhs.theLists) {
                for (const auto t : l) {
                    insert(t);
                }
            }
        }
        return *this;
    }

    int size() const { return curSize; }
    bool contains(const T &x) const
    {
        const auto whichList = theLists[myHash(x)];
        return find(whichList.cbegin(), whichList.cend(), x) != whichList.cend();
    }
    bool insert(const T &x)
    {
        auto &whichList = theLists[myHash(x)];
        if (find(whichList.cbegin(), whichList.cend(), x) != whichList.cend())
            return false;

        whichList.push_back(x);

        if (++curSize > theLists.size())
            rehash();

        return true;
    }
    bool remove(const T &x)
    {
        auto &whichList = theLists[myHash(x)];
        auto itr = find(whichList.cbegin(), whichList.cend(), x);
        if (itr == whichList.cend())
            return false;

        whichList.erase(itr);
        --curSize;
        return true;
    }

    void makeEmpty()
    {
        curSize = 0;
        for (auto &l : theLists) {
            l.clear();
        }
    }

private:
    void rehash()
    {
        auto oldLists = theLists;
        theLists.resize(nextPrime(int(theLists.size() << 1)));
        for (auto &l : theLists) {
            l.clear();
        }

        curSize = 0;
        for (const auto l : oldLists) {
            for (const auto t : l) {
                insert(t);
            }
        }
    }
    int myHash(const T &x) const
    {
        int hashVal = int(hash_value(x));
        hashVal %= theLists.size();
        if (hashVal < 0)
            hashVal += int(theLists.size());
        return hashVal;
    }
private:
    vector<list<T>> theLists;
    int curSize;
};

#endif // DS_CH05_HASHTABLE_SC_H
