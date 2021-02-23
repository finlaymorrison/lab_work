#include <iostream>
#include <random>
#include <utility>
#include <algorithm>

#ifdef SET_ENABLE_THREADING
#include <thread>
#endif

namespace math {

template<typename Ty, int N>
class matrix_row
{
private:

    Ty* elem;

public:

    constexpr matrix_row() noexcept :
        elem(nullptr)
    {}
    constexpr matrix_row(Ty* elem) noexcept :
        elem(elem)
    {}
    matrix_row(const matrix_row& row) = delete;
    constexpr matrix_row(matrix_row&& row) noexcept :
        elem(row.elem)
    {}
    ~matrix_row() = default;

    matrix_row& operator= (const matrix_row& row) = delete;
    matrix_row& operator= (matrix_row&& row) noexcept
    {
        elem = row.elem;
        return *this;
    }

    inline Ty& operator[] (int col) noexcept
    {
        return elem[col];
    }
};

template<typename Ty, int N>
class const_matrix_row
{
private:

    const Ty* elem;

public:

    constexpr const_matrix_row() noexcept :
        elem(nullptr)
    {}
    constexpr const_matrix_row(const Ty* elem) noexcept :
        elem(elem)
    {}
    const_matrix_row(const const_matrix_row& row) = delete;
    constexpr const_matrix_row(const_matrix_row&& row) :
        elem(row.elem)
    {}
    ~const_matrix_row() = default;

    const_matrix_row& operator= (const const_matrix_row& row) = delete;
    const_matrix_row& operator= (const_matrix_row&& row) noexcept
    {
        elem = row.elem;
        return *this;
    }

    inline Ty operator[] (int col) noexcept
    {
        return elem[col];
    }
};

template<typename Ty, int M, int N>
class matrix
{
private:

    Ty* elem;

public:

    matrix() :
        elem(new Ty[M * N])
    {}
    matrix(const matrix<Ty, M, N>& m) :
        elem(new Ty[M * N])
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                elem[i * N + j] = m.elem[i *  + j];
            }
        }
    }
    matrix(matrix<Ty, M, N>&& m) noexcept :
        elem(m.elem)
    {
        m.elem = nullptr;
    }

    ~matrix()
    {
        delete[] elem;
        elem = nullptr;
    }

    matrix<Ty, M, N>& operator= (const matrix<Ty, M, N>& m)
    {
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                elem[i * N + j] = m[i * N + j];
            }
        }
        return *this;
    }
    matrix<Ty, M, N>& operator= (matrix<Ty, M, N>&& m)
    {
        elem = m.elem;
        m.elem = nullptr;
        return *this;
    }

    inline matrix_row<Ty, N> operator[] (int row) noexcept
    {
        return {elem + row * N};
    }
    inline const_matrix_row<Ty, N> operator[] (int row) const noexcept
    {
        return {elem + row * N};
    }

    void zero() noexcept
    {

        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                elem[i * N + j] = 0;
            }
        }
    }
};

constexpr int BLOCK_SIZE = 128;

#ifdef SET_ENABLE_THREADING

template<typename Ty_a, typename Ty_b, int M, int N, int P>
void matrix_operator_mult_worker(const matrix<Ty_a, M, P>& a, const matrix<Ty_b, P, N>& b,
                                 matrix<decltype(Ty_a() * Ty_b()), M, N>& res, std::pair<int, int> blocks)
{
    constexpr int total_i_blocks = (M / BLOCK_SIZE) + ((M % BLOCK_SIZE) > 0);

    while (blocks.first < blocks.second)
    {
        const int i_b = (blocks.first % total_i_blocks) * BLOCK_SIZE;
        const int j_b = (blocks.first / total_i_blocks) * BLOCK_SIZE;

        for (int k = 0; k < P; ++k)
            for (int i = i_b; i < i_b + BLOCK_SIZE && i < M; ++i)
                for (int j = j_b; j < j_b + BLOCK_SIZE && j < N; ++j)
                    res[i][j] += a[i][k] * b[k][j];
        
        ++blocks.first;
    }
}

template<typename Ty_a, typename Ty_b, int M, int N, int P>
matrix<decltype(Ty_a() * Ty_b()), M, N> operator* (const matrix<Ty_a, M, P>& a, const matrix<Ty_b, P, N>& b)
{
    matrix<decltype(Ty_a() * Ty_b()), M, N> res;
    res.zero();

    const int thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads(thread_count);
    
    constexpr int total_i_blocks = (M / BLOCK_SIZE) + ((M % BLOCK_SIZE) > 0);
    constexpr int total_j_blocks = (N / BLOCK_SIZE) + ((N % BLOCK_SIZE) > 0);
    constexpr int total_blocks = total_i_blocks * total_j_blocks;
    const int blocks_per_thread = (total_blocks / thread_count) + 1;

    for (int i = 0; i < thread_count; ++i)
    {
        std::pair<int, int> block_bounds = std::make_pair(blocks_per_thread * i, std::min((i + 1) * blocks_per_thread, total_blocks));
        threads[i] = std::thread(matrix_operator_mult_worker<Ty_a, Ty_b, M, N, P>, std::ref(a), std::ref(b), std::ref(res), block_bounds);
    }

    for (int i = 0; i < thread_count; ++i)
    {
        threads[i].join();
    }

    return res;
}

#else

template<typename Ty_a, typename Ty_b, int M, int N, int P>
matrix<decltype(Ty_a() * Ty_b()), M, N> operator* (const matrix<Ty_a, M, P>& a, const matrix<Ty_b, P, N>& b)
{
    matrix<decltype(Ty_a() * Ty_b()), M, N> res;
    res.zero();

    for (int i_b = 0; i_b < M; i_b += BLOCK_SIZE)
        for (int j_b = 0; j_b < M; j_b += BLOCK_SIZE)
            for (int k = 0; k < P; ++k)
                for (int i = i_b; i < i_b + BLOCK_SIZE && i < M; ++i)
                    for (int j = j_b; j < j_b + BLOCK_SIZE && j < N; ++j)
                        res[i][j] += a[i][k] * b[k][j];

    return res;
}

#endif

template<typename Ty, int M, int N>
std::ostream& operator<< (std::ostream& os, matrix<Ty, M, N> mat)
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            os << mat[i][j] << '\t';
        }
        os << '\n';
    }
    return os;
}

}