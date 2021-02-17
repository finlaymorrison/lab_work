#include <iostream>
#include <complex>

using namespace std::complex_literals;

int main(int argc, char** argv) 
{
    std::complex<double> val = 2.4 + 1.2i;
    std::cout << val << std::endl;
    return 0;
}