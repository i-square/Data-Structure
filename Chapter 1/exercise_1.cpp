#include <iostream>

int main()
{
    int t;
    while (std::cout << "input a number:", std::cin >> t)
    {
        std::cout << std::endl << ones(t) << std::endl;
    }
    return 0;
}