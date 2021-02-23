#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <algorithm>

void fill_random(std::vector<double>& vec, size_t size)
{
   vec.resize(size);
   std::random_device rd;
   auto rng = std::bind(std::uniform_real_distribution<double>{10, 20}, std::default_random_engine{rd()});
   std::generate(vec.begin(), vec.end(), rng);
}

template<typename Ty>
std::ostream& operator<< (std::ostream& os, std::vector<Ty> vec)
{
    for (Ty& val : vec)
    {
        os << val << ' ';
    }
    return os;
}

int main(int argc, char** argv)
{
    std::vector<double> values(100);
    fill_random(values, 10);

    std::cout << values << std::endl;

    return 0;
}