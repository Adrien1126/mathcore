#include "mathcore/linalg/linalg_vector.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <stdexcept>

using mathcore::linalg::dot;
using mathcore::linalg::norm;
using mathcore::linalg::distance;
using mathcore::linalg::add;
using mathcore::linalg::subtract;
using mathcore::linalg::scale;
using mathcore::linalg::projection;

// -----------------------------------------------------------------------------
// FIXTURE DE BASE
// -----------------------------------------------------------------------------

class LinalgVectorTest : public ::testing::Test {
protected:
    std::vector<double> x3;
    std::vector<double> y3;
    std::vector<double> x2;

    void SetUp() override {
        x3 = {1.0, 2.0, 3.0};
        y3 = {4.0, 5.0, 6.0};
        x2 = {1.0, 2.0};
    }
};

// -----------------------------------------------------------------------------
// DOT PRODUCT
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, DotCorrectValue) {
    EXPECT_DOUBLE_EQ(dot(x3, y3), 32.0);
}

TEST_F(LinalgVectorTest, DotSymmetry) {
    EXPECT_DOUBLE_EQ(dot(x3, y3), dot(y3, x3));
}

TEST_F(LinalgVectorTest, DotThrowsOnSizeMismatch) {
    EXPECT_THROW(dot(x3, x2), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// NORM
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, NormPositive) {
    EXPECT_GT(norm(x3), 0.0);
}

TEST_F(LinalgVectorTest, NormSquaredEqualsDot) {
    EXPECT_NEAR(norm(x3) * norm(x3), dot(x3, x3), 1e-12);
}

// -----------------------------------------------------------------------------
// DISTANCE
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, DistanceZero) {
    EXPECT_DOUBLE_EQ(distance(x3, x3), 0.0);
}

TEST_F(LinalgVectorTest, DistanceSymmetry) {
    EXPECT_DOUBLE_EQ(distance(x3, y3), distance(y3, x3));
}

TEST_F(LinalgVectorTest, DistanceThrowsOnSizeMismatch) {
    EXPECT_THROW(distance(x3, x2), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// ADDITION
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, AddCorrectResult) {
    auto r = add(x3, y3);
    EXPECT_DOUBLE_EQ(r[0], 5.0);
    EXPECT_DOUBLE_EQ(r[1], 7.0);
    EXPECT_DOUBLE_EQ(r[2], 9.0);
}

TEST_F(LinalgVectorTest, AddThrowsOnSizeMismatch) {
    EXPECT_THROW(add(x3, x2), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// SUBTRACTION
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, SubtractCorrectResult) {
    auto r = subtract(y3, x3);
    EXPECT_DOUBLE_EQ(r[0], 3.0);
    EXPECT_DOUBLE_EQ(r[1], 3.0);
    EXPECT_DOUBLE_EQ(r[2], 3.0);
}

TEST_F(LinalgVectorTest, SubtractThrowsOnSizeMismatch) {
    EXPECT_THROW(subtract(x3, x2), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// SCALE
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, ScaleCorrectResult) {
    auto r = scale(x3, 2.0);
    EXPECT_DOUBLE_EQ(r[0], 2.0);
    EXPECT_DOUBLE_EQ(r[1], 4.0);
    EXPECT_DOUBLE_EQ(r[2], 6.0);
}

TEST_F(LinalgVectorTest, ScaleByZeroGivesZeroVector) {
    auto r = scale(x3, 0.0);
    EXPECT_DOUBLE_EQ(r[0], 0.0);
    EXPECT_DOUBLE_EQ(r[1], 0.0);
    EXPECT_DOUBLE_EQ(r[2], 0.0);
}

// -----------------------------------------------------------------------------
// PROJECTION
// -----------------------------------------------------------------------------

TEST_F(LinalgVectorTest, ProjectionParallelVector) {
    std::vector<double> u = {1.0, 0.0, 0.0};
    std::vector<double> x = {3.0, 0.0, 0.0};

    auto p = projection(x, u);
    EXPECT_DOUBLE_EQ(p[0], 3.0);
    EXPECT_DOUBLE_EQ(p[1], 0.0);
    EXPECT_DOUBLE_EQ(p[2], 0.0);
}

TEST_F(LinalgVectorTest, ProjectionOrthogonalVector) {
    std::vector<double> u = {1.0, 0.0, 0.0};
    std::vector<double> x = {0.0, 2.0, 0.0};

    auto p = projection(x, u);
    EXPECT_DOUBLE_EQ(p[0], 0.0);
    EXPECT_DOUBLE_EQ(p[1], 0.0);
    EXPECT_DOUBLE_EQ(p[2], 0.0);
}

TEST_F(LinalgVectorTest, ProjectionThrowsOnSizeMismatch) {
    EXPECT_THROW(projection(x3, x2), std::invalid_argument);
}
