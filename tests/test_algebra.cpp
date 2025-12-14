#include "mathcore/algebra.hpp"
#include <gtest/gtest.h>

//
// -----------------------------------------------------------------------------
// FIXTURE DE BASE (tests non paramétrés)
// -----------------------------------------------------------------------------

class AlgebraTest : public ::testing::Test {
protected:
  void SetUp() override {}
};

TEST_F(AlgebraTest, SolveLinearWithNoRoot) {
  EXPECT_THROW(mathcore::algebra::solveLinear(0, 1.0), std::invalid_argument);
}

TEST_F(AlgebraTest, SolveQuadraticWithNoRoot) {
  EXPECT_THROW(mathcore::algebra::solveQuadratic(1.0, 2.0, 2.0),
               std::domain_error);
}

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SOLVE_LINEAR
// -----------------------------------------------------------------------------

class AlgebraSolveLinearTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(AlgebraSolveLinearTest, SolveLinear) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::algebra::solveLinear(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Algebra_SolveLinear, AlgebraSolveLinearTest,
                         ::testing::Values(std::make_tuple(1, 0, 0),
                                           std::make_tuple(2, 1, -0.5)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SOLVE_QUADRATIC
// -----------------------------------------------------------------------------

class AlgebraSolveQuadraticTest
    : public ::testing::TestWithParam<
          std::tuple<double, double, double, std::pair<double, double>>> {};

TEST_P(AlgebraSolveQuadraticTest, SolveQuadratic) {
  auto [a, b, c, expected] = GetParam();
  auto roots = mathcore::algebra::solveQuadratic(a, b, c);
  EXPECT_NEAR(roots.first, expected.first, 1e-12);
  EXPECT_NEAR(roots.second, expected.second, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Algebra_SolveQuadratic, AlgebraSolveQuadraticTest,
    ::testing::Values(
        std::make_tuple(1, 2, 1, std::pair<double, double>{-1, -1}),
        std::make_tuple(1, -2, 1, std::pair<double, double>{1, 1}),
        std::make_tuple(1, -3, 2, std::pair<double, double>{1, 2}),
        std::make_tuple(0, 2, 4, std::pair<double, double>{-2, -2})));
