#ifndef LIST_H
#define LIST_H

template <typename Object>
class List() {
private:
    struct Node {
        Node(const Object &d = Object(), Node *p = nullptr, Node *n = nullptr)
            : data(d), prev(p), next(n) 
        { }
        Object data;
        Node *prev;
        Node *next;
    };
public:
    class const_iterator {
    public:
        const_iterator() : current(nullptr) { }
        const Object &operator*() const { return retrieve(); }
        const_iterator &operator++() 
        {
            current = current->next;
            return *this;
        }
        const_iterator &operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        { return current == rhs.current; }
        bool operator==(const const_iterator &rhs) const
        { return !(*this == rhs); }

    protected:
        friend class List<Object>;
        const_iterator(Node *p) : current(p) {}
        Node *current;
        Object &retrieve() const { return current->data; }
    };
    class iterator : public const_iterator {
    public:
        iterator() { }

        Object &operator*() { return retrieve(); }
        const Object &operator*() const { return const_iterator::operator*(); }

        iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        iterator &operator++(int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        friend class List<Object>;
        iterator(Node *p) : const_iterator(p) { }
    };

public:
    List() { init(); }
    List(const List &rhs)
    {
        init();
        *this = rhs;
    }
    ~List()
    {
        clear();
        delete head;
        delete tail;
    }

    const List &operator=(const List &rhs)
    {
        if (*this == rhs)
            return *this;
        clear();
        for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back(*itr);
        return *this;
    }

    iterator insert(iterator itr, const Object &x)
    {
        ;
    }

    iterator erase(iterator itr)
    {
        ;
    }
    iterator erase(iterator start, iterator end)
    {
        ;
    }
    
    bool empty() const { return size() == 0; }
    int size() const { return theSize; }
    void clear()
    {
        while (!empty())
            pop_front();
    }

    Object &front() { return *begin(); }
    const Object &front() const { return *begin(); }
    Object &back() { return *--end(); }
    const Object &back() const {  return *--end();  }

    void push_front(const Object &x) { insert(begin(), x); }
    void push_back(const Object &x) { insert(end(), x); }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    iterator begin() { return iterator(head->next); }
    const_iterator begin() const { return const_iterator(head->next); }
    iterator end() { return iterator(tail); }
    const_iterator end() const { return const_iterator(tail); }

private:
    void init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

private:
    int theSize;
    Node *head;
    Node *tail;
}

#endif // LIST_H
