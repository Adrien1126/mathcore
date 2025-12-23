#include "mathcore/linalg/linalg_small_matrix.hpp"

namespace mathcore::linalg {
double det2x2(const std::array<std::array<double, 2>, 2>& A) {
    return A[0][0] * A[1][1] - A[0][1] * A[1][0];  
}

double det3x3(const std::array<std::array<double, 3>, 3>& A) {
    return
    A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1])
  - A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0])
  + A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
} 

std::array<std::array<double, 2>, 2>
inverse2x2(const std::array<std::array<double, 2>, 2>& A)
{
    double det = det2x2(A);

    if (det == 0.0) {
        throw std::invalid_argument("Matrix is singular");
    }

    return {{
        {  A[1][1] / det, -A[0][1] / det },
        { -A[1][0] / det,  A[0][0] / det }
    }};
}

std::array<double, 2> solve2x2(const std::array<std::array<double, 2>, 2>& A, const std::array<double, 2>& b) {
    std::array<std::array<double, 2>, 2> invA = inverse2x2(A);
    return {
        invA[0][0] * b[0] + invA[0][1] * b[1], 
        invA[1][0] * b[0] + invA[1][1] * b[1]
    }; 
}
}