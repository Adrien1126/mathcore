#pragma once

namespace mathcore::arithmetic {
constexpr double add(double a, double b) { return a + b; }
constexpr double subtract(double a, double b) { return a - b; }
constexpr double multiply(double a, double b) { return a * b; }
double divide(double a, double b);

constexpr double min(double a, double b) { return (a < b ? a : b); }
constexpr double max(double a, double b) { return (a < b ? b : a); }
constexpr double abs(double a) { return (a < 0 ? -a : a); }
constexpr double sign(double a) { return (a > 0) - (a < 0); }
constexpr double clamp(double value, double low, double high) {
  return (value < low ? low : (value > high ? high : value));
}

constexpr double square(double a) { return a * a; }
constexpr double cube(double a) { return a * a * a; }
double inverse(double a);
} // namespace mathcore::arithmetic
