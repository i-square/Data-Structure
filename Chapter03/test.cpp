#include <iostream>

#include "SimpleCalculator.h"
#include "Queue.h"
#include "List.h"

using namespace std;

int main()
{
    SimpleCalculator cal("14+2-32+8*9+(54*7+92-4)");
    cout << cal.getResult() << endl;
    cout << cal.calcu("13+2-32+8*9+(54*7+92-4)") << endl;

    int a[20] = { 29, 14, 15, 84, 65, 85, 92, 81, 51, 13, 5, 18, -64, 89, 66, 21, 32, 27, 24, 52 };
    LinkQueue<int> que;
    SingleList<int> lst;
    List<int> dlst;

    for (int i = 0; i < 20; ++i) {
        que.enqueue(a[i]);
        lst.add(a[i]);
        dlst.push_back(a[i]);
    }

    cout << "queue: ";
    for (int i = 0; i < 20; ++i)
        cout << que.dequeue() << "→";
    cout << endl;

    cout << "single list: ";
    lst.print();

    cout << dlst.back() << " pop_back: ";
    dlst.pop_back();
    cout << dlst.back() << endl;

    getchar();

    return 0;
}