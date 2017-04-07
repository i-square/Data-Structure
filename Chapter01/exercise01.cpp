#include <iostream>

#include "exercise01.h"

int main()
{
    OrderedCollection<int> ARR;

    int temp = 0;
    cout << "Please input some numbers(-1 means end): ";
    while ((cin >> temp) && (temp != -1))
        ARR.insert(temp);
    
    if (ARR.size()) {
        cout << "Max number is: " << *ARR.findMax() << endl;
        cout << "Min number is: " << *ARR.findMin() << endl;
    }

    return 0;
}