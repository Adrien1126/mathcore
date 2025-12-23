#pragma once
#include <vector>

namespace mathcore::linalg {

// Produit scalaire : x ⋅ y
double dot(const std::vector<double>& x,
           const std::vector<double>& y);

// Norme euclidienne ||x||
double norm(const std::vector<double>& x);

// Distance euclidienne ||x - y||
double distance(const std::vector<double>& x,
                const std::vector<double>& y);

// Addition vectorielle x + y
std::vector<double> add(const std::vector<double>& x,
                        const std::vector<double>& y);

// Soustraction vectorielle x - y
std::vector<double> subtract(const std::vector<double>& x,
                             const std::vector<double>& y);

// Multiplication par un scalaire : αx
std::vector<double> scale(const std::vector<double>& x,
                          double alpha);

// Projection orthogonale de x sur u : proj_u (x)
std::vector<double> projection(const std::vector<double>& x,
                               const std::vector<double>& u);

} // namespace mathcore::linalg
