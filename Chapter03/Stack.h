#ifndef STACK_H
#define STACK_H

template <typename T>
class LinkStack {
private:
    struct Node {
        Node(const T &d = T(), Node *n = nullptr)
            : data(d), next(n)
        { }
        T data;
        Node *next;
    };

public:
    LinkStack() : stackSize(0), ptrTop(new Node()) { }
    LinkStack(const LinkStack &rhs) : stackSize(0), ptrTop(new Node()) { operator=(rhs); }
    ~LinkStack()
    {
        clear();
        delete ptrTop;
    }
    const LinkStack &operator=(const LinkStack &rhs)
    {
        if (this != &rhs) {
            clear();

            Node *src = rhs.ptrTop->next;
            Node *dest = ptrTop;

            while (src != nullptr) {
                Node *tmp = new Node(src->data);
                dest->next = tmp;
                dest = tmp;
                ++stackSize;
                src = src->next;
            }
        }
        return *this;
    }

    void push(const T &x)
    {
        Node *tmp = new Node(x);
        tmp->next = ptrTop->next;
        ptrTop->next = tmp;
        ++stackSize;
    }
    T &pop()
    {
        Node *oldTop = ptrTop;
        ptrTop = ptrTop->next;
        --stackSize;
        return oldTop->data;
    }
    const T &pop() const
    {
        Node *oldTop = ptrTop;
        ptrTop = ptrTop->next;
        --stackSize;
        return oldTop->data;
    }
    T &top()
    {
        return ptrTop->next->data;
    }
    const T &top() const
    {
        return ptrTop->next->data;
    }
    bool empty() const { return size() == 0; }
    int size() const { return stackSize; }
    void clear()
    {
        while (!empty())
            pop();
    }
    
private:
    int stackSize;
    Node *ptrTop;
};

template <typename T>
class ArrStack {
    enum { SPARE_CAPACITY = 16 };

public:
    explicit ArrStack(int initSize = 0)
        : topOfStack(-1), theCapacity(initSize + SPARE_CAPACITY)
    {
        theArray = new T[theCapacity];
    }
    ArrStack(const ArrStack &rhs) : theArray(nullptr)
    {
        operator=(rhs);
    }
    ~ArrStack()
    {
        delete[] theArray;
    }

    const ArrStack &operator=(const ArrStack &rhs)
    {
        if (this != &rhs) {
            delete[] theArray;
            topOfStack = rhs.topOfStack;
            theCapacity = rhs.theCapacity;

            theArray = new T[theCapacity];
            for (int i = 0; i < size(); ++i)
                theArray[i] = rhs.theArray[i];
        }
        return *this;
    }

    void push(const T &x)
    {
        if (++topOfStack == theCapacity)
            reserve(2 * theCapacity + 1);
        theArray[topOfStack] = x;
    }
    T &pop()
    {
        return theArray[topOfStack--];
    }
    const T &pop() const
    {
        return theArray[topOfStack--];
    }
    T &top()
    {
        return theArray[topOfStack];
    }
    const T &top() const
    {
        return theArray[topOfStack];
    }

    int size() const { return topOfStack + 1; }
    bool empty() const { return topOfStack == -1; }
    void clear()
    {
        while (!empty())
            pop();
    }

private:
    void reserve(int newCapacity)
    {
        T *oldArray = theArray;

        theArray = new T[newCapacity];
        for (int i = 0; i < size(); ++i)
            theArray[i] = oldArray[i];

        theCapacity = newCapacity;

        delete[] oldArray;
    }

private:
    int topOfStack;
    int theCapacity;
    T *theArray;
};

#endif //STACK_H