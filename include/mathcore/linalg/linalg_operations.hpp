#pragma once
#include <vector>

namespace mathcore::linalg {
    // Forme quadratique xᵀ A x
    double quadform(const std::vector<double>& x,
                const std::vector<std::vector<double>>& A);

    // Multiplication matrice-vecteur : A x
    std::vector<double> mulvec(const std::vector<std::vector<double>>& A,
                           const std::vector<double>& x);

    // Substitution arrière pour Ux = b (U triangulaire sup.)
    std::vector<double> back_substitution(const std::vector<std::vector<double>>& U,
                                      const std::vector<double>& b);
}