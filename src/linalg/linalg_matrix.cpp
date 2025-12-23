#include "mathcore/linalg/linalg_matrix.hpp"

namespace mathcore::linalg{
std::vector<std::vector<double>> mulmat(
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B)
{
    // 1. Vérifications de base
    if (A.empty() || B.empty()) {
        throw std::invalid_argument("Matrix A or B is empty");
    }

    // 2. Vérification du caractère rectangulaire de A
    const std::size_t m = A.size();
    const std::size_t n = A[0].size();

    for (std::size_t i = 1; i < m; ++i) {
        if (A[i].size() != n) {
            throw std::invalid_argument("Matrix A is not rectangular");
        }
    }

    // 3. Vérification du caractère rectangulaire de B
    const std::size_t p = B[0].size();

    for (std::size_t i = 0; i < B.size(); ++i) {
        if (B[i].size() != p) {
            throw std::invalid_argument("Matrix B is not rectangular");
        }
    }

    // 4. Compatibilité dimensionnelle
    if (n != B.size()) {
        throw std::invalid_argument("Incompatible matrix dimensions");
    }

    // 5. Allocation du résultat : m lignes, p colonnes
    std::vector<std::vector<double>> C(m, std::vector<double>(p, 0.0));

    // 6. Produit matriciel
    for (std::size_t i = 0; i < m; ++i) {
        for (std::size_t j = 0; j < p; ++j) {
            for (std::size_t k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& A){
    if (A.empty()){
        throw std::invalid_argument("Matrix A is empty");
    }
    const std::size_t n = A.size(); 
    const std::size_t m = A[0].size(); 

    // Vérification du caractère rectangulaire
    for (std::size_t i = 0; i < n; i++){
        if (A[i].size() != m){
            throw std::invalid_argument("Matrix A is not rectangular");
        }
    }

    std::vector<std::vector<double>> C(m, std::vector<double>(n, 0.0));
    for (std::size_t i = 0; i < n; i++){
        for (std::size_t j = 0; j< m; j++){
            C[j][i] = A[i][j]; 
        }
    } 
    return C; 
}
}
