#ifndef DS_CH04_EXERCISE04_H
#define DS_CH04_EXERCISE04_H

//ex4.11 未考虑end()如何实现
template <typename T>
class Set {
private:
    struct BinaryNode {
        BinaryNode() : left(nullptr), right(nullptr), parent(nullptr)
        {}
        BinaryNode(const T &element)
            : ele(element), left(nullptr), right(nullptr), parent(nullptr)
        {}
        BinaryNode(const T &element, BinaryNode *lt, BinaryNode *rt, BinaryNode *pt)
            : ele(element), left(lt), right(rt), parent(pt)
        {}
        T ele;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode *parent;
    };

public:
    class const_iterator {
    public:
        const_iterator() : current(nullptr) {}
        const T &operator*() const { return retrieve(); }
        const_iterator &operator++()
        {
            BinaryNode *t;
            if (current->right) { //若存在右儿子，则下一个是右子树的最小值
                t = current->right;
                while (t->left != nullptr)
                    t = t->left;
                current = t;
            } else { //否则上溯，若本身是右儿子则持续上溯
                t = current->parent;
                while (t != nullptr && t->ele < current->ele)
                    t = t->parent;
                current = t;
            }
            return *this;
        }
        const_iterator &operator++(int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const
        {
            return current == rhs.current;
        }
        bool operator!=(const const_iterator &rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        friend class Set<T>;
        const_iterator(BinaryNode *p) : current(p) {}
        T &retrieve() const { return current->ele; }
        BinaryNode *current;
    };

    class iterator : public const_iterator {
    public:
        iterator() {}

        T &operator*() { return retrieve(); }
        const T &operator*() const { return const_iterator::operator*(); }

        iterator &operator++()
        {
            BinaryNode *t;
            if (current->right) { //若存在右儿子，则下一个是右子树的最小值
                t = current->right;
                while (t->left != nullptr)
                    t = t->left;
                current = t;
            } else { //否则上溯，若本身是右儿子则持续上溯
                t = current->parent;
                while (t != nullptr && t->ele < current->ele)
                    t = t->parent;
                current = t;
            }
            return *this;
        }
        iterator &operator++(int)
        {
            iterator old = *this;
            ++(*this);
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
        friend class Set<T>;
        iterator(BinaryNode *p) : const_iterator(p) {}
    };

public:
    Set() : root(nullptr) {}
    Set(const Set &rhs) : root(nullptr) { operator=(rhs); }
    ~Set() { clear(); }

public:
    Set &operator=(const Set &rhs)
    {
        if (this != &rhs) {
            clear();
            const_iterator itr = rhs.begin();
            for (int i = 0; i < rhs.size(); ++i) {
                insert(*itr);
                ++itr;
            }
        }
        return *this;
    }

    iterator insert(const T &x) { return insert(x, root, root); }
    void erase(const T &x) { erase(x, root); }
    
    bool contains(const T &x) const { return contains(x, root); }
    bool empty() const { return size() == 0; }
    int size() const { return theSize; }
    void clear()
    {
        while (!empty())
            erase(*begin());
    }

    iterator begin()
    {
        BinaryNode *t = root;
        while (t->left != nullptr)
            t = t->left;
        return iterator(t);
    }
    const_iterator begin() const
    {
        BinaryNode *t = root;
        while (t->left != nullptr)
            t = t->left;
        return const_iterator(t);
    }

private:
    bool contains(const T &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->ele)
            return contains(x, t->left);
        else if (t->ele < x)
            return contains(x, t->right);
        else
            return true;
    }
    iterator insert(const T &x, BinaryNode *&t, BinaryNode *p)
    {
        if (t == nullptr) {
            t = new BinaryNode(x, nullptr, nullptr, p);
            ++theSize;
            return iterator(t);
        }
        else if (x < t->ele)
            return insert(x, t->left, t);
        else if (t->ele < x)
            return insert(x, t->right, t);
        return iterator(t);
    }
    void erase(const T &x, BinaryNode *&t)
    {
        if (t == nullptr)
            ;
        else if (x < t->ele)
            erase(x, t->left);
        else if (t->ele < x)
            erase(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) { //2 children
            BinaryNode *tmp = t->right;
            while (tmp->left != nullptr)
                tmp = tmp->left;
            t->ele = tmp->ele; //用右子树的最小值替代当前值
            erase(t->ele, t->right); //删掉右子树的最小值
        } else {
            BinaryNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            if (t != nullptr)
                t->parent = old->parent;
            delete old;
            --theSize;
        }
    }

private:
    int theSize;
    BinaryNode *root;
};

#endif // DS_CH04_EXERCISE04_H
