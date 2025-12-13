#include "mathcore/arithmetic.hpp"
#include <gtest/gtest.h>

//
// -----------------------------------------------------------------------------
// FIXTURE DE BASE (tests non paramétrés)
// -----------------------------------------------------------------------------
class ArithmeticTest : public ::testing::Test {
protected:
  // Si un jour tu veux ajouter un setup commun, ce sera ici
  void SetUp() override {}
};

TEST_F(ArithmeticTest, DivideByZero) {
  EXPECT_THROW(mathcore::arithmetic::divide(1.0, 0.0), std::invalid_argument);
}

TEST_F(ArithmeticTest, InverseZeroThrows) {
  EXPECT_THROW(mathcore::arithmetic::inverse(0.0), std::invalid_argument);
}

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — ADDITION
// -----------------------------------------------------------------------------
class ArithmeticAddTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticAddTest, Add) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::add(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_Add, ArithmeticAddTest,
                         ::testing::Values(std::make_tuple(1.0, 2.0, 3.0),
                                           std::make_tuple(-5.0, 5.0, 0.0),
                                           std::make_tuple(10.0, 20.0, 30.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SOUSTRACTION
// -----------------------------------------------------------------------------
class ArithmeticSubTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticSubTest, Subtract) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::subtract(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_Subtract, ArithmeticSubTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0, 1.0),
                                           std::make_tuple(-5.0, -5.0, 0.0),
                                           std::make_tuple(10.0, -20.0, 30.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MULTIPLICATION
// -----------------------------------------------------------------------------
class ArithmeticMulTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticMulTest, Multiply) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::multiply(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_Multiply, ArithmeticMulTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0, 2.0),
                                           std::make_tuple(-5.0, -5.0, 25.0),
                                           std::make_tuple(10.0, -20.0, -200.0),
                                           std::make_tuple(1.0, 0.0, 0.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — DIVISION
// -----------------------------------------------------------------------------

class ArithmeticDivTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticDivTest, Divide) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::divide(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_Divide, ArithmeticDivTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0, 2.0),
                                           std::make_tuple(-5.0, -5.0, 1.0),
                                           std::make_tuple(10.0, -20.0, -0.5)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MIN
// -----------------------------------------------------------------------------

class ArithmeticMinTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticMinTest, Minimum) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::min(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_min, ArithmeticMinTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0, 1.0),
                                           std::make_tuple(-5.0, -5.0, -5.0),
                                           std::make_tuple(10.0, -20.0,
                                                           -20.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MAX
// -----------------------------------------------------------------------------

class ArithmeticMaxTest
    : public ::testing::TestWithParam<std::tuple<double, double, double>> {};

TEST_P(ArithmeticMaxTest, Maximum) {
  auto [a, b, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::max(a, b), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_max, ArithmeticMaxTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0, 2.0),
                                           std::make_tuple(-5.0, -5.0, -5.0),
                                           std::make_tuple(10.0, -20.0, 10.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — ABS
// -----------------------------------------------------------------------------

class ArithmeticAbsTest
    : public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticAbsTest, Abs) {
  auto [a, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::abs(a), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_abs, ArithmeticAbsTest,
                         ::testing::Values(std::make_tuple(1.0, 1.0),
                                           std::make_tuple(0.0, 0.0),
                                           std::make_tuple(-1.0, 1.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SIGN
// -----------------------------------------------------------------------------

class ArithmeticSignTest
    : public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticSignTest, Sign) {
  auto [a, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::sign(a), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_sign, ArithmeticSignTest,
                         ::testing::Values(std::make_tuple(2.0, 1.0),
                                           std::make_tuple(0.0, 0.0),
                                           std::make_tuple(-2.0, -1.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — CLAMP
// -----------------------------------------------------------------------------

class ClampFixture {
protected:
  double low = -1.0;
  double high = 1.0;
};

class ArithmeticClampTest
    : public ClampFixture,
      public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticClampTest, Clamp) {
  auto [value, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::clamp(value, low, high), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(Arithmetic_Clamp, ArithmeticClampTest,
                         ::testing::Values(std::make_tuple(-2.0, -1.0),
                                           std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(0.0, 0.0),
                                           std::make_tuple(1.0, 1.0),
                                           std::make_tuple(2.0, 1.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SQUARE
// -----------------------------------------------------------------------------

class ArithmeticSquareTest
    : public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticSquareTest, Square) {
  auto [a, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::square(a), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticSquare, ArithmeticSquareTest,
                         ::testing::Values(std::make_tuple(0.0, 0.0),
                                           std::make_tuple(1.0, 1.0),
                                           std::make_tuple(-1.0, 1.0),
                                           std::make_tuple(2.0, 4.0),
                                           std::make_tuple(-2.0, 4.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — CUBE
// -----------------------------------------------------------------------------

class ArithmeticCubeTest
    : public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticCubeTest, Cube) {
  auto [a, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::cube(a), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticCube, ArithmeticCubeTest,
                         ::testing::Values(std::make_tuple(0.0, 0.0),
                                           std::make_tuple(1.0, 1.0),
                                           std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(2.0, 8.0),
                                           std::make_tuple(-2.0, -8.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — INVERSE
// -----------------------------------------------------------------------------

class ArithmeticInvTest
    : public ::testing::TestWithParam<std::tuple<double, double>> {};

TEST_P(ArithmeticInvTest, Inverse) {
  auto [a, expected] = GetParam();
  EXPECT_NEAR(mathcore::arithmetic::inverse(a), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(ArithmeticInv, ArithmeticInvTest,
                         ::testing::Values(std::make_tuple(1.0, 1.0),
                                           std::make_tuple(-1.0, -1.0),
                                           std::make_tuple(2.0, 0.5),
                                           std::make_tuple(-2.0, -0.5)));