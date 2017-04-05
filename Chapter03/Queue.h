#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"

template <typename T>
class LinkQueue : public List<T> {
public:
    void enqueue(const T &x)
    {
        push_back(x);
    }
    const T &dequeue()
    {
        T &temp = front();
        pop_front();
        return temp;
    }
};

#endif //QUEUE_H