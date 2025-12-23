#include "mathcore/linalg/linalg_operations.hpp"
#include <stdexcept>

namespace mathcore::linalg {
double quadform(const std::vector<double>& x,
                const std::vector<std::vector<double>>& A)
{
    if (x.empty() || A.empty()) {
        throw std::invalid_argument("Vector or matrix is empty");
    }

    const std::size_t n = x.size();

    // Vérification A carrée n×n
    if (A.size() != n) {
        throw std::invalid_argument("Matrix size incompatible with vector");
    }

    for (const auto& row : A) {
        if (row.size() != n) {
            throw std::invalid_argument("Matrix A is not square");
        }
    }

    double result = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            result += x[i] * A[i][j] * x[j];
        }
    }

    return result;
}

std::vector<double> mulvec(const std::vector<std::vector<double>>& A,
                           const std::vector<double>& x)
{
    if (A.empty() || x.empty()) {
        throw std::invalid_argument("Matrix or vector is empty");
    }

    const std::size_t m = A.size();
    const std::size_t n = x.size();

    for (const auto& row : A) {
        if (row.size() != n) {
            throw std::invalid_argument("Matrix and vector sizes are incompatible");
        }
    }

    std::vector<double> result(m, 0.0);

    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            result[i] += A[i][j] * x[j];
        }
    }

    return result;
}

std::vector<double> back_substitution(const std::vector<std::vector<double>>& U,
                                      const std::vector<double>& b)
{
    if (U.empty() || b.empty()) {
        throw std::invalid_argument("Matrix or vector is empty");
    }

    const std::size_t n = b.size();

    if (U.size() != n) {
        throw std::invalid_argument("Matrix and vector size mismatch");
    }

    for (std::size_t i = 0; i < n; ++i) {
        if (U[i].size() != n) {
            throw std::invalid_argument("Matrix U is not square");
        }
    }

    std::vector<double> x(n, 0.0);

    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        if (U[i][i] == 0.0) {
            throw std::invalid_argument("Matrix U is singular");
        }

        double sum = 0.0;
        for (std::size_t j = i + 1; j < n; ++j) {
            sum += U[i][j] * x[j];
        }

        x[i] = (b[i] - sum) / U[i][i];
    }

    return x;
}

} // namespace mathcore::linalg
