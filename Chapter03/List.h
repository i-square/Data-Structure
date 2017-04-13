#ifndef DS_CH03_LIST_H
#define DS_CH03_LIST_H

#include <stdexcept>

template <typename Object>
class List {
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
        const_iterator() : theList(nullptr), current(nullptr) { }
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
        const_iterator &operator--()
        {
            current = current->prev;
            return *this;
        }
        const_iterator &operator--(int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        { return current == rhs.current; }
        bool operator!=(const const_iterator &rhs) const
        { return !(*this == rhs); }

    protected:
        friend class List<Object>;
        const List<Object> *theList;
        const_iterator(const List<Object> &lst, Node *p) : theList(&lst), current(p) {}
        Node *current;
        Object &retrieve() const { return current->data; }
        void assertIsValid() const
        {
            if (theList == nullptr || current == nullptr || theList->head == current)
                throw std::runtime_error("Iterator out of bounds.");
        }
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
        iterator &operator--()
        {
            current = current->prev;
            return *this;
        }
        iterator &operator--(int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

        bool operator==(const iterator &rhs) const
        {
            return current == rhs.current;
        }
        bool operator!=(const iterator &rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        friend class List<Object>;
        iterator(const List<Object> &lst, Node *p) : const_iterator(lst, p) { }
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

    List &operator=(const List &rhs)
    {
        if (this == &rhs)
            return *this;
        clear();
        for (const_iterator itr = rhs.begin(); itr != rhs.end(); ++itr)
            push_back(*itr);
        return *this;
    }

    iterator insert(iterator itr, const Object &x)
    {
        itr.assertIsValid();
        if (itr.theList != this)
            throw std::logic_error("Iterator mismatch.");

        Node *p = itr.current;
        ++theSize;
        return iterator(*this, p->prev = p->prev->next = new Node(x, p->prev, p));
    }

    iterator erase(iterator itr)
    {
        itr.assertIsValid();
        if (itr.theList != this)
            throw std::logic_error("Iterator mismatch.");

        Node *p = itr.current;
        iterator retVal(*itr.theList, p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        --theSize;

        return retVal;
    }
    iterator erase(iterator start, iterator end)
    {
        start.assertIsValid();
        if (start.theList != this)
            throw std::logic_error("Iterator mismatch.");

        end.assertIsValid();
        if (end.theList != this)
            throw std::logic_error("Iterator mismatch.");

        iterator itr = start;
        while (itr != end)
            itr = erase(itr);
        return end;
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
    const Object &back() const {  return *--end(); }

    void push_front(const Object &x) { insert(begin(), x); }
    void push_back(const Object &x) { insert(end(), x); }

    void pop_front() { erase(begin()); }
    void pop_back() { erase(--end()); }

    iterator begin() { return iterator(*this, head->next); }
    const_iterator begin() const { return const_iterator(*this, head->next); }
    iterator end() { return iterator(*this, tail); }
    const_iterator end() const { return const_iterator(*this, tail); }

private:
    void init()
    {
        theSize = 0;
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

private:
    int theSize;
    Node *head;
    Node *tail;
};

//ex 3.11
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class SingleList {
private:
    struct Node {
        Node(const T &d = T(), Node *n = nullptr)
            : data(d), next(n)
        {
        }
        T data;
        Node *next;
    };

public:
    SingleList() { init(); }
    SingleList(const SingleList &rhs) { operator=(rhs); }
    ~SingleList() { eraseList(head); }

public:
    SingleList &operator=(const SingleList &rhs)
    {
        if (this != &rhs) {
            eraseList(head);
            init();

            theSize = rhs.theSize;

            Node *src = rhs.head;

            while (src != nullptr) {
                add(src->data);
                src = src->next;
            }
        }
        return *this;
    }

    bool add(const T &x)
    {
        if (contains(x))
            return false;
        else {
            Node *ptr = new Node(x);
            ptr->next = head->next;
            head->next = ptr;
            ++theSize;
        }
        return true;
    }
    bool remove(const T &x)
    {
        if (!contains(x))
            return false;
        else {
            Node *ptr = head->next;
            Node *trailer = nullptr;
            while (x != ptr->data) {
                trailer = ptr;
                ptr = ptr->next;
            }
            trailer->next = ptr->next;
            delete ptr;
            --theSize;
        }
        return true;
    }
    bool contains(const T &x)
    {
        Node *ptr = head->next;
        while (ptr != nullptr) {
            if (ptr->data == x)
                return true;
            else
                ptr = ptr->next;
        }
        return false;
    }
    void eraseList(Node *L)
    {
        Node *ptr = L;
        Node *nextPtr = nullptr;
        while (ptr != nullptr) {
            nextPtr = ptr->next;
            delete ptr;
            ptr = nextPtr;
        }
    }
    void print()
    {
        Node *ptr = head->next;
        while (ptr != nullptr) {
            cout << ptr->data << "¡ú";
            ptr = ptr->next;
        }
        cout << endl;
    }
    int size() const { return theSize; }

private:
    void init()
    {
        theSize = 0;
        head = new Node();
        head->next = nullptr;
    }

private:
    Node *head;
    int theSize;
};

#endif // DS_CH03_LIST_H
