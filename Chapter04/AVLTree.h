#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class AVLTree {
private:
    struct AVLNode {
        AVLNode (const T &element, AVLNode *lt, AVLNode *rt, int h = 0)
            : ele(element), left(lt), right(rt), height(h)
        {}
        T ele;
        AVLNode *left;
        AVLNode *right;
        int height;
    };

public:
    AVLTree() : root(nullptr) {}
    AVLTree(const AVLTree &rhs) { operator=(rhs); }
    ~AVLTree() { makeEmpty(); }

public:
    const AVLTree &operator=(const AVLTree &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    const T &findMin() const { return findMin(root)->ele; } //应保证非空调用
    const T &findMax() const { return findMax(root)->ele; } //应保证非空调用
    bool contains(const T &x) { return contains(x, root); }
    bool empty() const { return root == nullptr; }
    void printTree() const { printTree(root); }

    void makeEmpty() { makeEmpty(root); }
    void insert(const T &x) { insert(x, root); }
    void remove(const T &x) { remove(x, root); }

private:
    AVLNode *clone(AVLNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AVLNode(t->ele, clone(t->left), clone(t->right));
    }
    AVLNode *findMin(AVLNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }
    AVLNode *findMax(AVLNode *t) const
    {
        if (t != nullptr) {
            while (t->right != nullptr)
                t = t->right;
        }
        return t;
    }
    bool contains(const T &x, AVLNode *t)
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
    void printTree(AVLNode *t) const
    {
        if (t == nullptr)
            return;
        cout << t->ele << endl; //这句放的位置决定了前中后序遍历
        printTree(t->left);
        printTree(t->right);
    }
    void makeEmpty(AVLNode *&t)
    {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    void insert(const T &x, AVLNode *&t) const
    {
        if (t == nullptr)
            t = new AVLNode(x, nullptr, nullptr);
        else if (x < t->ele)
            insert(x, t->left);
        else if (t->ele < x)
            insert(x, t->right);
        else
            ; //do nothing
    }
    void remove(const T &x, AVLNode *&t) const
    {
    }

    int height(AVLNode *t) const { return t == nullptr ? -1 : t->height; }

private:
    AVLNode *root;
};

#endif //AVLTREE_H