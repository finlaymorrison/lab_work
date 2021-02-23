#include <vector>

#include "../complex.hpp"

std::vector<double> TridiagonalSolve(double E, std::vector<double>& D, std::vector<double>& R)
{
    const int n = D.size();

    std::vector<double> c(n);
    double id;

    std::vector<double> L(n);

    for (int i = 0; i < n; i++)
    {
        c[i] = E;
    }

    c[0] /= D[0];
    R[0] /= D[0];

    for (int i = 1; i < n; i++)
    {
        id = D[i] - c[i - 1] * E;
        c[i] /= id;
        R[i] = (R[i] - R[i - 1] * E) / id;
    }

    L[n - 1] = R[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        L[i] = R[i] - c[i] * L[i + 1];
    }

    return L;
}