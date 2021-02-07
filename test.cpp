#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
    std::vector<int> v;
    std::cout << "Size: " << v.size() << std::endl;
    v.insert(v.end(), 1);
    std::cout << "Size: " << v.size() << std::endl;
}