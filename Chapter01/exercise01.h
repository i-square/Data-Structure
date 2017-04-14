#ifndef DS_CH01_EXERCISE01_H
#define DS_CH01_EXERCISE01_H

// ex 1.5
int ones(int n)
{
    if (n < 2)
        return n;
    return (n & 1) + ones(n >> 1);
}

#include <vector>

using namespace std;

//ex 1.13
template <typename Object>
class Collection {
public:
    typedef typename vector<Object>::const_iterator const_iterator;
    typedef typename vector<Object>::size_type      size_type;

public:
    size_type size() const { return arr.size(); }
    bool isEmpty() const { return arr.empty(); }
    void makeEmpty() { arr.clear(); }
    bool contains(const Object &obj) { return _find(obj) != arr.cend(); }
    void insert(const Object &obj) { arr.push_back(obj); }
    void remove(const Object &obj)
    { 
        auto it = _find(obj);
        if (it != arr.cend())
            arr.erase(it);
    }
private:
    const_iterator _find(const Object &obj)
    {
        auto it = arr.cbegin();
        while (it != arr.cend()) {
            if (*it == obj)
                return it;
            ++it;
        }
        return it;
    }

private:
    vector<Object> arr;
};

//ex 1.14
template <typename Comparable>
class OrderedCollection {
    typedef typename vector<Comparable>::const_iterator const_iterator;
    typedef typename vector<Comparable>::size_type      size_type;

public:
    size_type size() const { return arr.size(); }
    bool isEmpty() const { return arr.empty(); }
    void makeEmpty() { arr.clear(); }
    void insert(const Comparable &obj) { arr.push_back(obj); }
    void remove(const Comparable &obj)
    {
        auto it = arr.cbegin();
        while (it != arr.cend()) {
            if (*it == obj) {
                arr.erase(it);
                break;
            }
        }
    }
    const_iterator findMin() const
    {
        size_type minIdx = 0;
        for (size_type i = 1; i < size(); ++i) {
            if (arr[minIdx] > arr[i])
                minIdx = i;
        }
        return arr.cbegin() + minIdx;
    }
    const_iterator findMax() const
    {
        size_type minIdx = 0;
        for (size_type i = 1; i < size(); ++i) {
            if (arr[minIdx] < arr[i])
                minIdx = i;
        }
        return arr.cbegin() + minIdx;
    }

private:
    vector<Comparable> arr;
};

#endif // DS_CH01_EXERCISE01_H
