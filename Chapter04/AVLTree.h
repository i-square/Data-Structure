#ifndef DS_CH04_AVLTREE_H
#define DS_CH04_AVLTREE_H

#include <algorithm>
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
    AVLTree &operator=(const AVLTree &rhs)
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
    int height(AVLNode *t) const { return t == nullptr ? -1 : t->height; }

    AVLNode *clone(AVLNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AVLNode(t->ele, clone(t->left), clone(t->right), t->height);
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
    void printDepth(const T &x, int depth = 0) const
    {
        while (depth--)
            cout << "\t";
        cout << "[" << x << "]" << endl;
    }
    void printTree(AVLNode *t, int depth = 0) const
    {
        if (t == nullptr)
            return; // do nothing
        printTree(t->left, depth + 1);
        printDepth(t->ele, depth); //这句放的位置决定了前中后序遍历
        printTree(t->right, depth + 1);
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

    // 针对情况1左左，节点和左儿子一起顺时针旋转
    void rotateWithLeft(AVLNode *&k2)
    {
        AVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1; // 右子树高度就是k2的高度

        k2 = k1; // 保证上一层节点链接到旋转后的节点
    }
    // 针对情况4右右，节点和右儿子一起逆时针旋转
    void rotateWithRight(AVLNode *&k1)
    {
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(k1->height, height(k2->right)) + 1; // 左子树高度就是k2的高度

        k1 = k2; // 保证上一层节点链接到旋转后的节点
    }
    // 针对情况2左右，节点的左儿子先逆时针旋转，接着节点顺时针旋转
    void doubleRotateWithLeft(AVLNode *&k3)
    {
        //rotateWithRight(k3->left);
        //rotateWithLeft(k3);

        //ex 3.26 编写一个双旋转，效率高于两次单旋转
        //分析旋转过程不难总结出来
        AVLNode *k1 = k3->left;
        AVLNode *k2 = k1->right;

        k1->right = k2->left;
        k3->left = k2->right;
        k2->left = k1;
        k2->right = k3;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k2->height = max(k1->height, k3->height) + 1;

        k3 = k2; // 保证上一层节点链接到旋转后的节点
    }
    // 针对情况3右左，节点的右儿子先顺时针旋转，接着节点逆时针旋转
    void doubleRotateWithRight(AVLNode *&k1) 
    {
        //rotateWithLeft(k3->right);
        //rotateWithRight(k3);

        //ex 3.26 编写一个双旋转，效率高于两次单旋转
        //分析旋转过程不难总结出来
        AVLNode *k3 = k1->right;
        AVLNode *k2 = k3->left;

        k1->right = k2->left;
        k3->left = k2->right;
        k2->left = k1;
        k2->right = k3;

        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        k2->height = max(k1->height, k3->height) + 1;

        k1 = k2; // 保证上一层节点链接到旋转后的节点
    }

    void insert(const T &x, AVLNode *&t)
    {
        if (t == nullptr)
            t = new AVLNode(x, nullptr, nullptr);
        else if (x < t->ele) {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->ele)
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else if (t->ele < x) {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (t->right->ele < x)
                    rotateWithRight(t);
                else
                    doubleRotateWithRight(t);
            }
        } else
            ; //do nothing
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    //AVLTree删除节点的思路:
    //1.像二叉查找树一样删除节点
    //2.重新计算节点高度
    //3.检查是否满足平衡条件，不满足需要调整
    void remove(const T &x, AVLNode *&t)
    {
        if (t == nullptr)
            return; //not found, do nothing
        if (x < t->ele) {
            remove(x, t->left);

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //删了左子树一个节点，需要判断右＞左
            if (height(t->right) - height(t->left) == 2) {
                if (height(t->right->right) >= height(t->right->left))
                    rotateWithRight(t);
                else
                    doubleRotateWithRight(t);
            }
        } else if (t->ele < x) {
            remove(x, t->right);

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //删了右子树一个节点，需要判断左＞右
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->left) >= height(t->left->right))
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else if (t->left != nullptr && t->right != nullptr) { //2 children
            t->ele = findMin(t->right)->ele; //用右子树的最小值替代当前值
            remove(t->ele, t->right); //删掉右子树的最小值

            t->height = std::max(height(t->left), height(t->right)) + 1;

            //删了右子树一个节点，需要判断左＞右
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->left) >= height(t->left->right))
                    rotateWithLeft(t);
                else
                    doubleRotateWithLeft(t);
            }
        } else {
            AVLNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }

private:
    AVLNode *root;
};

#endif // DS_CH04_AVLTREE_H
