#include <iostream>

#include "StackTest.h"

using namespace std;

int main()
{
    SimpleCalculator cal("14+2-32+8*9+(54*7+92-4)");
    cout << cal.getResult() << endl;
    cout << cal.calcu("13+2-32+8*9+(54*7+92-4)") << endl;

    return 0;
}