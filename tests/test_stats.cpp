#include "mathcore/stats.hpp"
#include <gtest/gtest.h>

//
// -----------------------------------------------------------------------------
// FIXTURE DE BASE (tests non paramétrés)
//

class StatsTest : public ::testing::Test {
protected:
  std::vector<double> empty_vec;

  void SetUp() override {
    empty_vec.clear(); // le vecteur est vide
  }
};

TEST_F(StatsTest, MeanEmpty) {
  EXPECT_THROW(mathcore::stats::mean(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, VariancePopulationEmpty) {
  EXPECT_THROW(mathcore::stats::variance_population(empty_vec),
               std::invalid_argument);
}

TEST_F(StatsTest, StdDevEmpty) {
  EXPECT_THROW(mathcore::stats::stddev(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, MinEmpty) {
  EXPECT_THROW(mathcore::stats::min(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, MaxEmpty) {
  EXPECT_THROW(mathcore::stats::max(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, RangeEmpty) {
  EXPECT_THROW(mathcore::stats::range(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, CenteredEmpty) {
  EXPECT_THROW(mathcore::stats::centered(empty_vec), std::invalid_argument);
}

TEST_F(StatsTest, NormalizeZscoreEmpty) {
  EXPECT_THROW(mathcore::stats::normalize_zscore(empty_vec),
               std::invalid_argument);
}

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MEAN
// -----------------------------------------------------------------------------

class StatsMeanTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsMeanTest, Mean) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::mean(v), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Mean, StatsMeanTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 2),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 0),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 1.0)));
                    
//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — VARIANCE_POPULATION
// -----------------------------------------------------------------------------

class StatsVariancePopulationTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsVariancePopulationTest, VariancePopulation) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::variance_population(v), expected, 1e-2);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Variance_Population, StatsVariancePopulationTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 0.66),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 0.66),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 0)));


//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — VARIANCE_SAMPLE
// -----------------------------------------------------------------------------

class StatsVarianceSampleTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsVarianceSampleTest, VarianceSample) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::variance_sample(v), expected, 1e-2);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Variance_Sample, StatsVarianceSampleTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 1),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 1),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — STDDEV
// -----------------------------------------------------------------------------

class StatsStddevTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsStddevTest, Stddev) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::stddev(v), expected, 1e-2);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_stddev, StatsStddevTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 0.82),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 0.82),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — SUM
// -----------------------------------------------------------------------------

class StatsSumTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsSumTest, Sum) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::sum(v), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Sum, StatsSumTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 6.0),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 0),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 3.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MIN
// -----------------------------------------------------------------------------

class StatsMinTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsMinTest, Min) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::min(v), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Min, StatsMinTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 1.0),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, -1.0),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 1.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — MAX
// -----------------------------------------------------------------------------

class StatsMaxTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsMaxTest, Max) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::max(v), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Max, StatsMaxTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 3.0),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 1.0),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 1.0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — RANGE
// -----------------------------------------------------------------------------

class StatsRangeTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, double>> {
};

TEST_P(StatsRangeTest, Range) {
  auto [v, expected] = GetParam();
  EXPECT_NEAR(mathcore::stats::range(v), expected, 1e-12);
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Range, StatsRangeTest,
    ::testing::Values(std::make_tuple(std::vector<double>{1.0, 2.0, 3.0}, 2.0),
                      std::make_tuple(std::vector<double>{-1.0, 0, 1.0}, 2.0),
                      std::make_tuple(std::vector<double>{1.0, 1.0, 1.0}, 0)));

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — CENTERED
// -----------------------------------------------------------------------------

class StatsCenteredTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, std::vector<double>>> {
};

TEST_P(StatsCenteredTest, Centered) {
    auto [v, expected] = GetParam();

    mathcore::stats::centered(v); // transformation IN PLACE

    ASSERT_EQ(v.size(), expected.size());

    for (std::size_t i = 0; i < v.size(); ++i) {
        EXPECT_NEAR(v[i], expected[i], 1e-12);
    }
}

INSTANTIATE_TEST_SUITE_P(
    Stats_Centered, StatsCenteredTest,
    ::testing::Values(
        std::make_tuple(std::vector<double>{1.0, 2.0, 3.0},
                        std::vector<double>{-1.0, 0.0, 1.0}),
        std::make_tuple(std::vector<double>{-1.0, 0.0, 1.0},
                        std::vector<double>{-1.0, 0.0, 1.0}),
        std::make_tuple(std::vector<double>{1.0, 1.0, 1.0},
                        std::vector<double>{0.0, 0.0, 0.0})
    )
);

//
// -----------------------------------------------------------------------------
// TESTS PARAMÉTRÉS — NORMALIZE Z-SCORE
// -----------------------------------------------------------------------------

class StatsZScoreTest
    : public ::testing::TestWithParam<std::tuple<std::vector<double>, std::vector<double>>> {
};

TEST_P(StatsZScoreTest, NormalizeZScore) {
    auto [v, expected] = GetParam();

    mathcore::stats::normalize_zscore(v); // transformation IN PLACE

    ASSERT_EQ(v.size(), expected.size());

    for (std::size_t i = 0; i < v.size(); ++i) {
        EXPECT_NEAR(v[i], expected[i], 1e-12);
    }
}

INSTANTIATE_TEST_SUITE_P(
    Stats_ZScore, StatsZScoreTest,
    ::testing::Values(

        // Cas simple : données symétriques
        std::make_tuple(
            std::vector<double>{1.0, 2.0, 3.0},
            std::vector<double>{
                (1.0 - 2.0) / std::sqrt((1.0 + 0.0 + 1.0) / 3.0),   // -1 / sqrt(2/3)
                (2.0 - 2.0) / std::sqrt((1.0 + 0.0 + 1.0) / 3.0),   // 0
                (3.0 - 2.0) / std::sqrt((1.0 + 0.0 + 1.0) / 3.0)    // +1 / sqrt(2/3)
            }),

        // Cas déjà centré
        std::make_tuple(
            std::vector<double>{-1.0, 0.0, 1.0},
            std::vector<double>{
                -1.0 / std::sqrt((1 + 0 + 1) / 3.0),
                 0.0,
                 1.0 / std::sqrt((1 + 0 + 1) / 3.0)
            }),

        // Cas constant → tous les z doivent être 0
        std::make_tuple(
            std::vector<double>{5.0, 5.0, 5.0},
            std::vector<double>{0.0, 0.0, 0.0}
        )
    )
);
