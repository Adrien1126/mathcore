#include "mathcore/linalg/linalg_matrix.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

using mathcore::linalg::mulmat;
using mathcore::linalg::transpose;

// -----------------------------------------------------------------------------
// FIXTURE DE BASE
// -----------------------------------------------------------------------------

class LinalgMatrixTest : public ::testing::Test {
protected:
    std::vector<std::vector<double>> A2x2;
    std::vector<std::vector<double>> B2x2;
    std::vector<std::vector<double>> A2x3;
    std::vector<std::vector<double>> B3x2;
    std::vector<std::vector<double>> non_rectangular;

    void SetUp() override {
        A2x2 = {
            {1.0, 2.0},
            {3.0, 4.0}
        };

        B2x2 = {
            {5.0, 6.0},
            {7.0, 8.0}
        };

        A2x3 = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        };

        B3x2 = {
            {7.0, 8.0},
            {9.0, 10.0},
            {11.0, 12.0}
        };

        non_rectangular = {
            {1.0, 2.0},
            {3.0}
        };
    }
};

// -----------------------------------------------------------------------------
// MULMAT — CAS NOMINAUX
// -----------------------------------------------------------------------------

TEST_F(LinalgMatrixTest, MulMat2x2) {
    auto C = mulmat(A2x2, B2x2);

    EXPECT_DOUBLE_EQ(C[0][0], 19.0);
    EXPECT_DOUBLE_EQ(C[0][1], 22.0);
    EXPECT_DOUBLE_EQ(C[1][0], 43.0);
    EXPECT_DOUBLE_EQ(C[1][1], 50.0);
}

TEST_F(LinalgMatrixTest, MulMatRectangular) {
    auto C = mulmat(A2x3, B3x2);

    EXPECT_EQ(C.size(), 2);
    EXPECT_EQ(C[0].size(), 2);

    EXPECT_DOUBLE_EQ(C[0][0], 58.0);
    EXPECT_DOUBLE_EQ(C[0][1], 64.0);
    EXPECT_DOUBLE_EQ(C[1][0], 139.0);
    EXPECT_DOUBLE_EQ(C[1][1], 154.0);
}

// -----------------------------------------------------------------------------
// MULMAT — ERREURS
// -----------------------------------------------------------------------------

TEST_F(LinalgMatrixTest, MulMatThrowsOnEmptyMatrix) {
    std::vector<std::vector<double>> empty;
    EXPECT_THROW(mulmat(empty, B2x2), std::invalid_argument);
    EXPECT_THROW(mulmat(A2x2, empty), std::invalid_argument);
}

TEST_F(LinalgMatrixTest, MulMatThrowsOnNonRectangularA) {
    EXPECT_THROW(mulmat(non_rectangular, B2x2), std::invalid_argument);
}

TEST_F(LinalgMatrixTest, MulMatThrowsOnNonRectangularB) {
    EXPECT_THROW(mulmat(A2x2, non_rectangular), std::invalid_argument);
}

TEST_F(LinalgMatrixTest, MulMatThrowsOnIncompatibleDimensions) {
    EXPECT_THROW(mulmat(A2x2, B3x2), std::invalid_argument);
}

// -----------------------------------------------------------------------------
// TRANSPOSE — CAS NOMINAUX
// -----------------------------------------------------------------------------

TEST_F(LinalgMatrixTest, Transpose2x2) {
    auto T = transpose(A2x2);

    EXPECT_DOUBLE_EQ(T[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T[0][1], 3.0);
    EXPECT_DOUBLE_EQ(T[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T[1][1], 4.0);
}

TEST_F(LinalgMatrixTest, TransposeRectangular) {
    auto T = transpose(A2x3);

    EXPECT_EQ(T.size(), 3);
    EXPECT_EQ(T[0].size(), 2);

    EXPECT_DOUBLE_EQ(T[0][0], 1.0);
    EXPECT_DOUBLE_EQ(T[0][1], 4.0);
    EXPECT_DOUBLE_EQ(T[1][0], 2.0);
    EXPECT_DOUBLE_EQ(T[1][1], 5.0);
    EXPECT_DOUBLE_EQ(T[2][0], 3.0);
    EXPECT_DOUBLE_EQ(T[2][1], 6.0);
}

// -----------------------------------------------------------------------------
// TRANSPOSE — ERREURS
// -----------------------------------------------------------------------------

TEST_F(LinalgMatrixTest, TransposeThrowsOnEmptyMatrix) {
    std::vector<std::vector<double>> empty;
    EXPECT_THROW(transpose(empty), std::invalid_argument);
}

TEST_F(LinalgMatrixTest, TransposeThrowsOnNonRectangularMatrix) {
    EXPECT_THROW(transpose(non_rectangular), std::invalid_argument);
}
