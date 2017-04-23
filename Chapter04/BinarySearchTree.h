#ifndef DS_CH04_BINARYSEARCHTREE_H
#define DS_CH04_BINARYSEARCHTREE_H

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class BinarySearchTree {
private:
    struct BinaryNode {
        BinaryNode (const T &element, BinaryNode *lt, BinaryNode *rt)
            : ele(element), left(lt), right(rt)
        {}
        T ele;
        BinaryNode *left;
        BinaryNode *right;
    };

public:
    BinarySearchTree() : root(nullptr) {}
    BinarySearchTree(const BinarySearchTree &rhs) { operator=(rhs); }
    ~BinarySearchTree() { makeEmpty(); }

public:
    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    const T &findMin() const { return findMin(root)->ele; } //应保证非空调用
    const T &findMax() const { return findMax(root)->ele; } //应保证非空调用
    bool contains(const T &x) const { return contains(x, root); }
    bool empty() const { return root == nullptr; }
    void printTree() const { printTree(root); }

    void makeEmpty() { makeEmpty(root); }
    void insert(const T &x) { insert(x, root); }
    void remove(const T &x) { remove(x, root); }

private:
    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new BinaryNode(t->ele, clone(t->left), clone(t->right));
    }
    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr) {
            while (t->right != nullptr)
                t = t->right;
        }
        return t;
    }
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
    void printDepth(const T &x, int depth = 0) const
    {
        while (depth--)
            cout << "\t";
        cout << "[" << x << "]" << endl;
    }
    void printTree(BinaryNode *t, int depth = 0) const
    {
        if (t == nullptr)
            return; // do nothing
        printTree(t->left, depth + 1);
        printDepth(t->ele, depth); //这句放的位置决定了前中后序遍历
        printTree(t->right, depth + 1);
    }
    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    void insert(const T &x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode(x, nullptr, nullptr);
        else if (x < t->ele)
            insert(x, t->left);
        else if (t->ele < x)
            insert(x, t->right);
        else
            ; //do nothing
    }
    void remove(const T &x, BinaryNode *&t)
    {
        if (t == nullptr)
            ; //not found, do nothing
        if (x < t->ele)
            remove(x, t->left);
        else if (t->ele < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) { //2 children
            t->ele = findMin(t->right)->ele; //用右子树的最小值替代当前值
            remove(t->ele, t->right); //删掉右子树的最小值
        } else {
            BinaryNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }

private:
    BinaryNode *root;
};

#endif // DS_CH04_BINARYSEARCHTREE_H
