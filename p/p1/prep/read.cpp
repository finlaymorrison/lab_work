#include <fstream>
#include <iostream>
#include <vector>

template<typename TYPE>
std::ostream& operator<< (std::ostream& os, std::vector<TYPE> vec)
{
    os << '{';
    for (int i = 0; i < vec.size() - 1; ++i)
    {
        os << vec[i] << ',';
    }
    return os << vec.back() << '}';

}

int main(int argc, char** argv)
{
    std::vector<char> chars;
    std::ifstream file("input-data.txt");
    char c;
    while (file >> c)
    {
        chars.push_back(c);
    }
    file.close();
    std::cout << chars << std::endl;
    return 0;
}