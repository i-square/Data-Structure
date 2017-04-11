#include <iostream>
#include <random>
#include <chrono>

using namespace std;

#include "HashTable(Separate_Chaining).h"
#include "HashTable(Open_Addressing_Hashing).h"

int main()
{
    default_random_engine e(static_cast<unsigned int>(time(nullptr)));
    uniform_int_distribution<int> u(0, 10000);

    int arr[10000] = { 0 };
    for (int i = 0; i < 10000; ++i)
        arr[i] = u(e);

    HashTable_SC<int> tableSC(100);
    HashTable_OAH<int> tableOAH(100);

    for (int i = 0; i < 10000; ++i) {
        tableSC.insert(arr[i]);
        tableOAH.insert(arr[i]);
    }

    cout << "SC size: " << tableSC.size() << ", find " << arr[5] << " ? " 
         << boolalpha << tableSC.contains(arr[5]) << endl;
    cout << "OAH size: " << tableOAH.size() << ", find " << arr[5] << " ? "
        << boolalpha << tableOAH.contains(arr[5]) << endl;

    getchar();
    return 0;
}
