#include "mathcore/algebra.hpp"
#include <cmath>
#include <stdexcept>

namespace mathcore::algebra {
double solveLinear(double a, double b) {
  if (a == 0) {
    throw std::invalid_argument("solveLinear : a must not be 0");
  }
  return -b / a;
}

std::pair<double, double> solveQuadratic(double a, double b, double c) {
  if (a == 0) {
    return {solveLinear(b, c), solveLinear(b, c)};
  }
  double d = discriminant(a, b, c);
  if (d < 0) {
    throw std::domain_error("No real roots");
  }
  double root1 = (-b - std::sqrt(d)) / (2 * a);
  double root2 = (-b + std::sqrt(d)) / (2 * a);
  return {root1, root2};
}
} // namespace mathcore::algebra
