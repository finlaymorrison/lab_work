/*
 * Project: p4
 * File: p4/main.cpp
 * -----
 * File Created: Monday, 22nd February 2021 12:56:35 am
 * Author: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Last Modified: Thursday, 18th March 2021 2:30:59 am
 * Modified By: Finlay Morrison (morrison.fin02@gmail.com)
 * -----
 * Copyright (CC BY-SA) 2021 Finlay Morrison
 */

#include <random>
#include <iostream>
#include <functional>
#include <type_traits>
#include <chrono>

#include "complex.hpp"
#include "matrix.hpp"

template<typename Ty, typename Generator=std::default_random_engine, 
         typename Distribution=std::uniform_real_distribution<double>>
math::complex<double> random_complex()
{
    std::random_device rd;
    auto rng = std::bind(Distribution{0, 10}, Generator{rd()});
    return {rng(), rng()};
}

template<typename Ty, int M, int N, typename Generator=std::default_random_engine, 
         typename Distribution=std::uniform_real_distribution<double>>
void fill_random(math::matrix<math::complex<Ty>, M, N>& mat)
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            mat[i][j] = random_complex<Ty, Generator, Distribution>();
        }
    }
}

template<typename Ty, int M, int N, typename Generator=std::default_random_engine, 
         typename Distribution=std::uniform_real_distribution<double>>
void fill_random(math::matrix<Ty, M, N>& mat)
{
    std::random_device rd;
    auto rng = std::bind(Distribution{0, 10}, Generator{rd()});
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            mat[i][j] = rng();
        }
    }
}

class timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
public:
    timer() :
        t_start(std::chrono::high_resolution_clock::now())
    {}
    ~timer()
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> t_end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count() / 1000.0 << std::endl;
    }
};

template<typename Ty, int M, typename Generator=std::default_random_engine, 
         typename Distribution=std::uniform_real_distribution<double>>
math::matrix<double, M, M> make_random_tridiagonal()
{
    std::random_device rd;
    auto rng = std::bind(Distribution{0, 10}, Generator{rd()});

    math::matrix<Ty, M, M> mat;

    for (int i = 0; i < M; ++i)
    {
        mat[i][i] = rng();
    }
    Ty off_diagonal = rng();
    for (int i = 1; i < M; ++i)
    {
        mat[i-1][i] = off_diagonal;
        mat[i][i-1] = off_diagonal;
    }

    return mat;
}

template<typename Ty, int M, typename Generator=std::default_random_engine, 
         typename Distribution=std::uniform_real_distribution<double>>
math::matrix<math::complex<Ty>, M, M> make_random_complex_tridiagonal()
{

    math::matrix<math::complex<Ty>, M, M> mat;

    for (int i = 0; i < M; ++i)
    {
        mat[i][i] = random_complex<Ty, Generator, Distribution>();
    }
    math::complex<Ty> off_diagonal = random_complex<Ty, Generator, Distribution>();
    for (int i = 1; i < M; ++i)
    {
        mat[i-1][i] = off_diagonal;
        mat[i][i-1] = off_diagonal;
    }

    return mat;
}

int main(int argc, char** argv)
{
    
    math::matrix<math::complex<double>, 5, 5> tridiag = make_random_complex_tridiagonal<double, 5, std::default_random_engine, std::uniform_real_distribution<double>>();
    math::matrix<math::complex<double>, 5, 1> res;
    fill_random(res);

    std::cout << tridiag << std::endl;
    std::cout << "x\n" << std::endl;
    std::cout << res << std::endl;
    std::cout << "=\n" << std::endl;
    math::matrix<math::complex<double>, 5, 1> rhs = tridiag * res;
    std::cout << rhs << std::endl;

    math::matrix<math::complex<double>, 5, 1> recalculated_res = tridiag.solve_tridiagonal(rhs);
    std::cout << "recalculated result vector:\n" << std::endl;
    std::cout << recalculated_res << std::endl;   

    return 0;
}