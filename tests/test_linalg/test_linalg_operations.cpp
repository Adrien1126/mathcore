#include "mathcore/linalg/linalg_operations.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using mathcore::linalg::quadform;
using mathcore::linalg::mulvec;
using mathcore::linalg::back_substitution;

// -----------------------------------------------------------------------------
// FIXTURE DE BASE
// -----------------------------------------------------------------------------

class LinalgOperationsTest : public ::testing::Test {
protected:
    std::vector<double> x3;
    std::vector<std::vector<double>> A3;
    std::vector<std::vector<double>> U3;
    std::vector<double> b3;

    void SetUp() override {
        x3 = {1.0, 2.0, 3.0};

        A3 = {
            {4.0, 1.0, 2.0},
            {1.0, 3.0, 0.0},
            {2.0, 0.0, 5.0}
        };

        // Matrice triangulaire supérieure
        U3 = {
            {2.0, -1.0,  3.0},
            {0.0,  4.0, -2.0},
            {0.0,  0.0,  5.0}
        };

        b3 = {5.0, 6.0, 10.0};
    }
};

// -----------------------------------------------------------------------------
// QUADFORM
// -----------------------------------------------------------------------------

TEST_F(LinalgOperationsTest, QuadformCorrectValue) {
    // xᵀ A x = 1*(4*1 + 1*2 + 2*3)
    //        + 2*(1*1 + 3*2 + 0*3)
    //        + 3*(2*1 + 0*2 + 5*3)
    //        = 4 + 2 + 6 + 2 + 12 + 0 + 6 + 0 + 45 = 77

    EXPECT_DOUBLE_EQ(quadform(x3, A3), 77.0);
}

TEST_F(LinalgOperationsTest, QuadformThrowsOnSizeMismatch) {
    std::vector<double> x2 = {1.0, 2.0};
    EXPECT_THROW(quadform(x2, A3), std::invalid_argument);
}

TEST_F(LinalgOperationsTest, QuadformThrowsOnNonSquareMatrix) {
    std::vector<std::vector<double>> non_square = {
        {1.0, 2.0},
        {3.0, 4.0},
        {5.0, 6.0}
    };
    EXPECT_THROW(quadform(x3, non_square), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// MULVEC
// -----------------------------------------------------------------------------

TEST_F(LinalgOperationsTest, MulVecCorrectValue) {
    auto y = mulvec(A3, x3);

    EXPECT_DOUBLE_EQ(y[0], 12.0); // 4*1 + 1*2 + 2*3
    EXPECT_DOUBLE_EQ(y[1], 7.0);  // 1*1 + 3*2 + 0*3
    EXPECT_DOUBLE_EQ(y[2], 17.0); // 2*1 + 0*2 + 5*3
}

TEST_F(LinalgOperationsTest, MulVecThrowsOnSizeMismatch) {
    std::vector<double> x2 = {1.0, 2.0};
    EXPECT_THROW(mulvec(A3, x2), std::invalid_argument);
}

TEST_F(LinalgOperationsTest, MulVecThrowsOnEmptyMatrix) {
    std::vector<std::vector<double>> empty;
    EXPECT_THROW(mulvec(empty, x3), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// BACK SUBSTITUTION
// -----------------------------------------------------------------------------

TEST_F(LinalgOperationsTest, BackSubstitutionCorrectSolution) {
    // Résolution :
    // 5z = 10      -> z = 2
    // 4y - 2z = 6  -> y = 2.5
    // 2x - y + 3z = 5 -> x = 0.75

    auto x = back_substitution(U3, b3);

    EXPECT_NEAR(x[0], 0.75, 1e-12);
    EXPECT_NEAR(x[1], 2.5,  1e-12);
    EXPECT_NEAR(x[2], 2.0,  1e-12);
}

TEST_F(LinalgOperationsTest, BackSubstitutionThrowsOnSingularMatrix) {
    std::vector<std::vector<double>> U_singular = {
        {1.0, 2.0},
        {0.0, 0.0}
    };
    std::vector<double> b = {1.0, 2.0};

    EXPECT_THROW(back_substitution(U_singular, b), std::invalid_argument);
}

TEST_F(LinalgOperationsTest, BackSubstitutionThrowsOnSizeMismatch) {
    std::vector<double> b2 = {1.0, 2.0};
    EXPECT_THROW(back_substitution(U3, b2), std::invalid_argument);
}
