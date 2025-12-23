#include "mathcore/linalg/linalg_small_matrix.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using mathcore::linalg::det2x2;
using mathcore::linalg::det3x3;
using mathcore::linalg::inverse2x2;
using mathcore::linalg::solve2x2;

// -----------------------------------------------------------------------------
// FIXTURE DE BASE
// -----------------------------------------------------------------------------

class LinalgSmallMatrixTest : public ::testing::Test {
protected:
    std::array<std::array<double, 2>, 2> A2;
    std::array<std::array<double, 2>, 2> A2_singular;
    std::array<std::array<double, 3>, 3> A3;
    std::array<double, 2> b2;

    void SetUp() override {
        A2 = {{
            {1.0, 2.0},
            {3.0, 4.0}
        }};

        A2_singular = {{
            {1.0, 2.0},
            {2.0, 4.0}
        }};

        A3 = {{
            { 6.0,  1.0, 1.0},
            { 4.0, -2.0, 5.0},
            { 2.0,  8.0, 7.0}
        }};

        b2 = {5.0, 11.0};
    }
};

// -----------------------------------------------------------------------------
// DET 2x2
// -----------------------------------------------------------------------------

TEST_F(LinalgSmallMatrixTest, Det2x2CorrectValue) {
    EXPECT_DOUBLE_EQ(det2x2(A2), -2.0);
}

TEST_F(LinalgSmallMatrixTest, Det2x2Singular) {
    EXPECT_DOUBLE_EQ(det2x2(A2_singular), 0.0);
}

// -----------------------------------------------------------------------------
// DET 3x3
// -----------------------------------------------------------------------------

TEST_F(LinalgSmallMatrixTest, Det3x3CorrectValue) {
    // déterminant connu = -306
    EXPECT_DOUBLE_EQ(det3x3(A3), -306.0);
}

// -----------------------------------------------------------------------------
// INVERSE 2x2
// -----------------------------------------------------------------------------

TEST_F(LinalgSmallMatrixTest, Inverse2x2CorrectResult) {
    auto invA = inverse2x2(A2);

    EXPECT_NEAR(invA[0][0], -2.0, 1e-12);
    EXPECT_NEAR(invA[0][1],  1.0, 1e-12);
    EXPECT_NEAR(invA[1][0],  1.5, 1e-12);
    EXPECT_NEAR(invA[1][1], -0.5, 1e-12);
}

TEST_F(LinalgSmallMatrixTest, Inverse2x2ThrowsIfSingular) {
    EXPECT_THROW(inverse2x2(A2_singular), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// SOLVE 2x2
// -----------------------------------------------------------------------------

TEST_F(LinalgSmallMatrixTest, Solve2x2CorrectSolution) {
    // Système :
    // [1 2][x] = [ 5]
    // [3 4][y]   [11]
    //
    // solution : x = 1, y = 2

    auto x = solve2x2(A2, b2);

    EXPECT_NEAR(x[0], 1.0, 1e-12);
    EXPECT_NEAR(x[1], 2.0, 1e-12);
}

TEST_F(LinalgSmallMatrixTest, Solve2x2ThrowsIfSingular) {
    EXPECT_THROW(solve2x2(A2_singular, b2), std::invalid_argument);
}
