#pragma once

#include <utility>

namespace mathcore::algebra {
double solveLinear(double a, double b);

constexpr double discriminant(double a, double b, double c) {
  return b * b - 4 * a * c;
}

std::pair<double, double> solveQuadratic(double a, double b, double c);
} // namespace mathcore::algebra
