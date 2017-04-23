#ifndef DS_CH06_LEFTISTHEAP_H
#define DS_CH06_LEFTISTHEAP_H

#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class LeftistHeap {
private:
    struct LeftistNode {
        LeftistNode(const T &theEle, LeftistNode *lt = nullptr, 
            LeftistNode *rt = nullptr, int np = 0)
            : ele(theEle), left(lt), right(rt), npl(np) {}
        LeftistNode *left;
        LeftistNode *right;
        int npl;
        T ele;
    };

public:
    LeftistHeap() : root(nullptr) {}
    LeftistHeap(const LeftistHeap &rhs) { operator=(rhs); }
    ~LeftistHeap() { makeEmpty(); }

public:
    LeftistHeap &operator=(const LeftistHeap &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    bool empty() const { return root == nullptr; }
    const T &findMin() const { return root->ele; } //应保证非空调用

    void printTree() const { printTree(root); }
    //插入可以看成是合并一个单节点堆，时间界也是O(logN)
    void insert(const T &x)
    {
        root = merge(new LeftistNode(x), root);
    }
    //删除可以看成是删除根结点，再合并左右子树，时间界也是O(logN)
    void deleteMin()
    {
        if (empty())
            throw std::underflow_error("当前堆为空");

        LeftistNode *oldRoot = root;
        root = merge(root->left, root->right);
        delete oldRoot;
    }
    void deleteMin(T &minItem)
    {
        minItem = findMin();
        deleteMin();
    }
    void makeEmpty() { makeEmpty(root); }
    //合并两个堆的时间界为O(logN)
    void merge(LeftistHeap &rhs)
    {
        if (this != &rhs) {
            root = merge(root, rhs.root);
            rhs.makeEmpty();
        }
    }

private:
    void printDepth(const T &x, int depth = 0) const
    {
        while (depth--)
            cout << "\t";
        cout << "[" << x << "]" << endl;
    }
    void printTree(LeftistNode *t, int depth = 0) const
    {
        if (t == nullptr)
            return; // do nothing
        printTree(t->left, depth + 1);
        printDepth(t->ele, depth); //这句放的位置决定了前中后序遍历
        printTree(t->right, depth + 1);
    }
    void makeEmpty(LeftistNode *&t)
    {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }
    LeftistNode *clone(LeftistNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new LeftistNode(t->ele, clone(t->left), clone(t->right), t->npl);
    }
    LeftistNode *merge(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;
        return h1->ele < h2->ele ? merge1(h1, h2) : merge1(h2, h1);
    }
    LeftistNode *merge1(LeftistNode *h1, LeftistNode *h2)
    {
        if (h1->left == nullptr) {
            h1->left = h2;
        } else {
            h1->right = merge(h1->right, h2);
            if (h1->left->npl < h1->right->npl)
                swapChildren(h1);
            h1->npl = h1->right->npl + 1;
        }
        return h1;
    }
    void swapChildren(LeftistNode *t)
    {
        LeftistNode *temp = t->left;
        t->left = t->right;
        t->right = temp;
    }

private:
    LeftistNode *root;
};

#endif // DS_CH06_LEFTISTHEAP_H
