#ifndef DS_CH03_VECTOR_H
#define DS_CH03_VECTOR_H

#include <stdexcept>

template <typename Object>
class Vector {
    enum { SPARE_CAPACITY = 16 };
    typedef Object       *iterator;
    typedef const Object *const_iterator;

public:
    explicit Vector(int initSize = 0)
        : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY)
    {
        objects = new Object[theCapacity];
    }
    Vector(const Vector &rhs) : objects(nullptr)
    {
        operator=(rhs);
    }
    ~Vector()
    {
        delete[] objects;
    }

    Vector &operator=(const Vector &rhs)
    {
        if (this != &rhs) {
            delete[] objects;
            theSize = rhs.size();
            theCapacity = rhs.capacity();

            objects = new Object[theCapacity];
            for (int i = 0; i < size(); ++i)
                objects[i] = rhs.objects[i];
        }
        return *this;
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2 + 1);
        theSize = newSize;
    }

    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;
        Object *oldArray = objects;
        
        objects = new Object[newCapacity];
        for (int i = 0; i < theSize; ++i)
            objects[i] = oldArray[i];

        theCapacity = newCapacity;

        delete[] oldArray;
    }

    Object &operator[](int index)
    {
        // ex3.7 添加边界检测
        if (index >= 0 && index < size())
            return objects[index];
        else
            throw std::runtime_error("index out of bounds");
    }
    const Object &operator[](int index) const
    {
        // ex3.7 添加边界检测
        if (index >= 0 && index < size())
            return objects[index];
        else
            throw std::runtime_error("index out of bounds");
    }
    
    bool empty() const { return size() == 0; }
    void clear() { theSize = 0; }
    int size() const { return theSize; }
    int capacity() const { return theCapacity;}

    void push_back(const Object &x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void pop_back() { --theSize; }

    const Object &back() const { return objects[theSize - 1]; }

    iterator begin() { return &objects[0]; }
    const_iterator begin() const { return &objects[0]; }
    iterator end() { return &objects[size()]; }
    const_iterator end() const { return &objects[size()]; }

private:
    int theSize;
    int theCapacity;
    Object *objects;
};

#endif // DS_CH03_VECTOR_H
