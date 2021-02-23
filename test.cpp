#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    std::random_device rd;

    for (int i = 0; i  < 100; ++i)
    {
        std::cout << rd() << std::endl;
    }
}