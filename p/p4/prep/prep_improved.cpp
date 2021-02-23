#include <iostream>
#include <random>
#include <algorithm>

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
                elem[i * N + j] = m.elem[i * N + j];
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
};

int main(int argc, char** argv)
{
    matrix<double, 100, 100> mat;

    std::random_device rd;
    auto rng = std::bind(std::uniform_real_distribution<double>{10, 20}, std::default_random_engine{rd()});

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            mat[i][j] = rng();
        }
    }

    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            std::cout << mat[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << std::flush;

    return 0;
}