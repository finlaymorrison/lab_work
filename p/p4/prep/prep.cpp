#include <iostream>
#include <random>
#include <vector>
#include <functional>
#include <algorithm>

template<typename Ty>
class matrix
{
private:

    std::vector<std::vector<Ty>> elem;

public:

    matrix() = default;

    matrix(const matrix<Ty>& mat) :
        elem(mat.elem)
    {}
    matrix(matrix<Ty>&& mat) noexcept :
        elem(std::move(mat.elem))
    {}

    matrix(const std::vector<std::vector<Ty>>& vec) :
        elem(vec)
    {}
    matrix(std::vector<std::vector<Ty>>&& vec) noexcept :
        elem(std::move(vec))
    {}

    matrix(int i, int j) :
        elem(i, std::vector<Ty>(j))
    {}

    ~matrix() = default;

    matrix& operator= (const matrix<Ty>& mat)
    {
        elem.resize(mat.elem.size());
        for (int i = 0; i < mat.elem.size(); ++i)
        {
            elem[i].resize(mat.elem[i].size());
            for (int j = 0; j < mat.elem[i].size(); ++i)
            {
                elem[i][j] = mat.elem[i][j];
            }
        }
        return *this;
    }
    matrix& operator= (matrix<Ty>&& mat) noexcept
    {
        elem = std::move(mat.elem);
        return *this;
    }

    matrix& operator= (const std::vector<std::vector<Ty>>& vec)
    {
        elem.resize(vec.size());
        for (int i = 0; i < vec.size(); ++i)
        {
            elem[i].resize(vec[i].size());
            for (int j = 0; j < vec[i].size(); ++i)
            {
                elem[i][j] = vec[i][j];
            }
        }
        return *this;
    }
    matrix& operator= (std::vector<std::vector<Ty>>&& vec) noexcept
    {
        elem = std::move(vec);
        return *this;
    }

    std::vector<Ty>& operator[] (size_t index) noexcept
    {
        return elem[index];
    }
    std::vector<Ty> operator[] (size_t index) const noexcept
    {
        return elem[index];
    }

    inline size_t size() const noexcept
    {
        return elem.size();
    };

    void random_matrix();
};

void fill_random(std::vector<double>& vec)
{
    std::random_device rd;
    auto rng = std::bind(std::uniform_real_distribution<double>{10, 20}, std::default_random_engine{rd()});
    std::generate(vec.begin(), vec.end(), rng);
}

template<typename Ty>
void matrix<Ty>::random_matrix()
{
    for (int i = 0; i < elem.size(); ++i)
    {
        fill_random(elem[i]);
    }
}

template<typename Ty>
std::ostream& operator<< (std::ostream& os, matrix<Ty>& mat)
{
    for (int i = 0; i < mat.size(); ++i)
    {
        for (int j = 0; j < mat[i].size(); ++j)
        {
            os << mat[i][j] << '\t';
        }
        os << '\n';
    }
    return os;
}

int main(int argc, char** argv)
{
    matrix<double> mat(10, 10);
    mat.random_matrix();

    std::cout << mat << std::endl;

    return 0;
}