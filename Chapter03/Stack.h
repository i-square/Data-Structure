#ifndef DS_CH03_STACK_H
#define DS_CH03_STACK_H

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
    LinkStack() : stackSize(0), head(nullptr) { }
    LinkStack(const LinkStack &rhs) : stackSize(0), head(nullptr) { operator=(rhs); }
    ~LinkStack() { clear(); }
    LinkStack &operator=(const LinkStack &rhs)
    {
        if (this != &rhs) {
            clear();

            Node *src = rhs.head;

            while (src != nullptr) {
                push(src->data);
                src = src->next;
            }
        }
        return *this;
    }

    void push(const T &x)
    {
        Node *ptr = new Node(x, head);
        head = ptr;
        ++stackSize;
    }
    void pop()
    {
        Node *ptr = head->next;
        delete head;
        head = ptr;
        --stackSize;
    }
    T &top()
    {
        return head->data;
    }
    const T &top() const
    {
        return head->data;
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
    Node *head;
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

    ArrStack &operator=(const ArrStack &rhs)
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

#endif // DS_CH03_STACK_H
