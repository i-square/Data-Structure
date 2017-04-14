#ifndef DS_CH03_QUEUE_H
#define DS_CH03_QUEUE_H

#include "List.h"

template <typename T>
class LinkQueue {
private:
    struct Node {
        Node(const T &d = T(), Node *n = nullptr)
            : data(d), next(n)
        {}
        T data;
        Node *next;
    };
    
public:
    LinkQueue() : front(nullptr), rear(nullptr) {}
    LinkQueue(const LinkQueue &rhs) { operator=(rhs); }
    ~LinkQueue() { clear(); }

public:
    LinkQueue &operator=(const LinkQueue &rhs)
    {
        if (this != &rhs) {
            clear();

            Node *src = rhs.front;
            while (src != nullptr) {
                enqueue(src->data);
                src = src->next;
            }
        }
        return *this;
    }

    void enqueue(const T &x)
    {
        Node *ptr = new Node(x);
        if (rear != nullptr)
            rear = rear->next = ptr;
        else
            front = rear = ptr;
    }
    T dequeue()
    {
        T tmp = front->data;
        Node *ptr = front;
        if (front->next == nullptr)
            front = rear = nullptr;
        else
            front = front->next;
        delete ptr;
        return tmp;
    }
    void clear()
    {
        while (front != nullptr)
            dequeue();
    }

private:
    Node *front;
    Node *rear;
};

#include <vector>
using std::vector;

template <typename T>
class ArrQueue {
public:
    ArrQueue(int size = 16) : maxSize(size), front(0), rear(0) { theArray.resize(maxSize); }
    ArrQueue(const ArrQueue &rhs) { operator=(rhs); }
    ~ArrQueue() { clear(); }

public:
    ArrQueue &operator=(const ArrQueue &rhs)
    {
        if (this != &rhs) {
            clear();

            front = rhs.front;
            rear = rhs.rear;
            maxSize = rhs.maxSize;
            theArray.resize(maxSize);
            for (int i = 0; i < maxSize; ++i)
                theArray[i] = rhs.theArray[i];
        }
        return *this;
    }

    void enqueue(const T &x)
    {
        if (!full()) {
            theArray[rear] = x;
            rear = (rear + 1) % maxSize;
        }
    }
    T dequeue()
    {
        T tmp = theArray[front];
        front = (front + 1) % maxSize;
        return tmp;
    }
    void clear()
    {
        while (!empty())
            dequeue();
    }
    bool empty() const { return front == rear; }
    bool full() const { return (rear + 1) % maxSize == front; }

private:
    int front, rear;
    int maxSize;
    vector<T> theArray;
};

#endif // DS_CH03_QUEUE_H
