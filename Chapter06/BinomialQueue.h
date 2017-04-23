#ifndef DS_CH06_BINOMIALQUEUE_H
#define DS_CH06_BINOMIALQUEUE_H

#include <algorithm>
#include <vector>
#include <stdexcept>

using std::cout;
using std::endl;

template <typename T>
class BinomialQueue {
    enum { DEFAULT_TREES = 1 };
private:
    struct BinomialNode {
        BinomialNode(const T &theElement, BinomialNode *lt, BinomialNode *rt)
            : element(theElement), leftChild(lt), nextSibling(rt)
        {}
        T element;
        BinomialNode *leftChild;
        BinomialNode *nextSibling;
    };

public:
    BinomialQueue() : curSize(0), theTrees(DEFAULT_TREES) { init(); }
    explicit BinomialQueue(const T &x) : curSize(0), theTrees(DEFAULT_TREES)
    {
        init();
        ++curSize;
        theTrees[0] = new BinomialNode(x, nullptr, nullptr);
    }
    BinomialQueue(const BinomialQueue &rhs) { operator=(rhs); }
    ~BinomialQueue()
    {
        makeEmpty();
    }

public:
    BinomialQueue &operator=(const BinomialQueue &rhs)
    {
        if (this != &rhs) {
            makeEmpty();
            curSize = rhs.curSize;
            theTrees.resize(rhs.capacity());
            init();
            for (int i = 0; i < rhs.curSize; ++i) {
                if (rhs.theTrees[i] != nullptr)
                    theTrees[i] = clone(rhs.theTrees[i]);
            }
        }
        return *this;
    }

    void printForest() const
    {
        for (const auto t : theTrees) {
            if (t != nullptr) {
                printTree(t);
                cout << "=============================================" << endl;
            }
        }
    }

    bool empty() const { return curSize == 0; }
    const T &findMin() const
    {
        if (empty())
            throw std::underflow_error("空二项队列");
        return theTrees[findMinIndex()]->element;
    }

    void insert(const T &x)
    {
        merge(BinomialQueue(x));
    }
    void deleteMin()
    {
        if (empty())
            throw std::underflow_error("空二项队列");

        int minIndex = findMinIndex();
        BinomialNode *oldRoot = theTrees[minIndex];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // H'' 长度是min所在tree - 1（去掉min）
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize(minIndex + 1);
        deletedQueue.curSize = (1 << minIndex) - 1;
        for (int j = minIndex - 1; j >= 0; --j) {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }

        // H' size是去掉H''和min
        theTrees[minIndex] = nullptr;
        curSize -= deletedQueue.curSize + 1;

        merge(deletedQueue);
    }
    void deleteMin(T &minItem)
    {
        if (empty())
            throw std::underflow_error("空二项队列");

        int minIndex = findMinIndex();
        minItem = theTrees[minIndex]->element;

        BinomialNode *oldRoot = theTrees[minIndex];
        BinomialNode *deletedTree = oldRoot->leftChild;
        delete oldRoot;

        // H'' 长度是min所在tree - 1（去掉min）
        BinomialQueue deletedQueue;
        deletedQueue.theTrees.resize(minIndex + 1);
        deletedQueue.curSize = (1 << minIndex) - 1;
        for (int j = minIndex - 1; j >= 0; --j) {
            deletedQueue.theTrees[j] = deletedTree;
            deletedTree = deletedTree->nextSibling;
            deletedQueue.theTrees[j]->nextSibling = nullptr;
        }

        // H' size是去掉H''和min
        theTrees[minIndex] = nullptr;
        curSize -= deletedQueue.curSize + 1;

        merge(deletedQueue);
    }

    void makeEmpty()
    {
        for (auto &t : theTrees) {
            deleteTree(t);
        }
        curSize = 0;
    }
    void merge(BinomialQueue &rhs)
    {
        if (this == &rhs)
            return;

        curSize += rhs.curSize;

        if (curSize > capacity()) {
            auto oldNumTrees = theTrees.size();
            auto newNumTrees = std::max(theTrees.size(), rhs.theTrees.size()) + 1;
            theTrees.resize(newNumTrees);
            for (auto i = oldNumTrees; i < newNumTrees; ++i)
                theTrees[i] = nullptr;
        }

        BinomialNode *carry = nullptr; //用来进位
        for (int i = 0, j = 1; j <= curSize; ++i, j <<= 1) {
            BinomialNode *t1 = theTrees[i];
            BinomialNode *t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

            int whichCase = t1 == nullptr ? 0 : 1;
            whichCase += t2 == nullptr ? 0 : 2;
            whichCase += carry == nullptr ? 0 : 4;

            switch (whichCase) {
            case 0: //空树
            case 1: //rhs空
                break;
            case 2: //this空
                theTrees[i] = t2;
                break;
            case 4: //只有carry
                theTrees[i] = carry;
                carry = nullptr;
                break;
            case 3: //this和rhs
                carry = combineTrees(t1, t2);
                theTrees[i] = rhs.theTrees[i] = nullptr;
                break;
            case 5: //this和carry
                carry = combineTrees(t1, carry);
                theTrees[i] = nullptr;
                break;
            case 6: //rhs和carry
                carry = combineTrees(t2, carry);
                rhs.theTrees[i] = nullptr;
                break;
            case 7: //都有
                theTrees[i] = carry;
                carry = combineTrees(t1, t2);
                rhs.theTrees[i] = nullptr;
                break;
            }
        }

        rhs.init();
    }

private:
    void printDepth(const T &x, int depth = 0) const
    {
        while (depth--)
            cout << "\t";
        cout << "[" << x << "]" << endl;
    }
    void printTree(BinomialNode *t, int depth = 0) const
    {
        if (t == nullptr)
            return; // do nothing
        printTree(t->leftChild, depth + 1);
        printDepth(t->element, depth); //这句放的位置决定了前中后序遍历
        printTree(t->nextSibling, depth + 1);
    }
    void init()
    {
        curSize = 0;
        for (auto &t : theTrees)
            t = nullptr;
    }
    void deleteTree(BinomialNode *&t)
    {
        if (t != nullptr) {
            deleteTree(t->leftChild);
            deleteTree(t->nextSibling);
            delete t;
            t = nullptr;
        }
    }
    int findMinIndex() const
    {
        int i = 0, minIndex = 0;
        while (theTrees[i] == nullptr)
            ++i;
        for (minIndex = i; i < theTrees.size(); ++i) {
            if (theTrees[i] != nullptr &&
                theTrees[i]->element < theTrees[minIndex]->element) {
                minIndex = i;
            }
        }
        return minIndex;
    }
    int capacity() const { return static_cast<int>(theTrees.capacity()); }
    BinomialNode *combineTrees(BinomialNode *t1, BinomialNode *t2)
    {
        if (t2->element < t1->element)
            return combineTrees(t2, t1);
        t2->nextSibling = t1->leftChild;
        t1->leftChild = t2;
        return t1;
    }
    BinomialNode *clone(BinomialNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        return new BinomialNode(t->element, clone(t->leftChild), clone(t->nextSibling));
    }

private:
    int curSize;
    vector<BinomialNode *> theTrees; //若13个元素，则theTrees里是[0 0 0 0 1 1 0 1]存储
};

#endif // DS_CH06_BINOMIALQUEUE_H
