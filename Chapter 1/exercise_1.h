#ifndef EXERCISE_1_H
#define EXERCISE_1_H

// ex 1.5
int ones(int n)
{
    if (n < 2)
        return n;
    return (n & 1) + ones(n >> 1);
}

//ex 1.13
#include <vector>

template <typename Object>
class Collection {
public:
    Collection() {}

public:
    bool isEmpty() const { return arr.empty(); }
    void makeEmpty() { arr.clear(); }
    bool contains(Object &obj) { return _find(obj) != arr.cend(); }
    void insert(Object &obj) { arr.push_back(obj); }
    void remove(Object &obj)
    { 
        if ((vector<Object>::const_iterator it = _find(obj)) != arr.cend())
            arr.erase(it);
    }

private:
    vector<Object>::const_iterator &_find(Object &obj)
    {
        for (vector<Object>::const_iterator it = arr.cbegin();
            it != arr.cend(); ++it)
        {
            if (*it == obj)
                return it;
        }
        return it;
    }

private:
    vector<Object> arr;
};

#endif //EXERCISE_1_H
