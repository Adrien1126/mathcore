#include "mathcore/linalg/linalg_vector.hpp"
#include <cmath>
#include <stdexcept>

namespace mathcore::linalg {
double dot(const std::vector<double> &x, const std::vector<double> &y)
{
    if (x.size() != y.size()) {
        throw std::invalid_argument("The size are different"); 
    }
    double sum = 0; 
    for (std::size_t i = 0; i < x.size(); i++) {
        sum += x[i] * y[i]; 
    }
    return sum; 
}

double norm(const std::vector<double>& x) {
    return std::sqrt(dot(x, x)); 
}

double distance(const std::vector<double> &x, const std::vector<double> &y)
{
    if (x.size() != y.size()) {
        throw std::invalid_argument("The size are different"); 
    }
    return norm(subtract(x, y));
}

std::vector<double> add(const std::vector<double> &x, const std::vector<double> &y)
{
    if (x.size() != y.size()) {
        throw std::invalid_argument("The size are different"); 
    }
    std::vector<double> v(x.size()); 
    for (std::size_t i = 0; i < x.size(); i++) {
        v[i] = x[i] + y[i]; 
    }
    return v; 
}

std::vector<double> subtract(const std::vector<double> &x, const std::vector<double> &y)
{
    if (x.size() != y.size()) {
        throw std::invalid_argument("The size are different"); 
    }
    std::vector<double> v(x.size()); 
    for (std::size_t i = 0; i < x.size(); i++) {
        v[i] = x[i] - y[i]; 
    }
    return v; 
}

std::vector<double> scale(const std::vector<double> &x, double alpha)
{
    std::vector<double> v(x.size()); 
    for (std::size_t i = 0; i < x.size(); i++) {
        v[i] = alpha * x[i]; 
    }
    return v; 
}

std::vector<double> projection(const std::vector<double> &x, const std::vector<double> &u)
{
    if (x.size() != u.size()) {
        throw std::invalid_argument("The size are different"); 
    }
    std::vector<double> v(x.size()); 
    double alpha = dot(x, u) / dot(u, u); 
    v = scale(u, alpha); 
    return v; 
}
}




