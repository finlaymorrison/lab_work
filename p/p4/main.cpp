#include <chrono>

#define SET_ENABLE_THREADING
#include "matrix.hpp"

constexpr int SIZE = 4096;

int main(int argc, char** argv)
{
    math::matrix<double, SIZE, SIZE> m0;
    math::matrix<double, SIZE, SIZE> m1;

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<> dist(0, 10);
    
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            m0[i][j] = dist(eng);
            m1[i][j] = dist(eng);
        }
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> t_start(std::chrono::high_resolution_clock::now());
    math::matrix<double, SIZE, SIZE> m_res = m0 * m1;
    std::chrono::time_point<std::chrono::high_resolution_clock> t_end(std::chrono::high_resolution_clock::now());
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count() / 1000.0 << 's' << std::endl;
    return 0;
}