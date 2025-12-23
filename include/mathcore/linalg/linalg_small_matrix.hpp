#pragma once
#include <array>

namespace mathcore::linalg {

// Déterminant d’une matrice 2×2
double det2x2(const std::array<std::array<double, 2>, 2>& A);

// Déterminant d’une matrice 3×3
double det3x3(const std::array<std::array<double, 3>, 3>& A);

// Inverse d’une matrice 2×2
std::array<std::array<double, 2>, 2> inverse2x2(
    const std::array<std::array<double, 2>, 2>& A);

// Résolution du système 2×2 A x = b
std::array<double, 2> solve2x2(
    const std::array<std::array<double, 2>, 2>& A,
    const std::array<double, 2>& b);

} // namespace mathcore::linalg
