#pragma once
#include <vector>

namespace mathcore::linalg {
// Multiplication matrice-matrice : A B
// Vérification, matrice rectangulaire et non vide
std::vector<std::vector<double>> mulmat(const std::vector<std::vector<double>>& A,
                                        const std::vector<std::vector<double>>& B);

// Transposée d'une matrice Aᵀ
std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& A);
} // namespace mathcore::linalg
