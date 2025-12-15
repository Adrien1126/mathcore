#pragma once
#include <vector>

namespace mathcore::stats {
double mean(const std::vector<double> &v);
double variance_population(const std::vector<double> &v);
double variance_sample(const std::vector<double> &v);
double stddev(const std::vector<double> &v);
double sum(const std::vector<double> &v);
double min(const std::vector<double> &v);
double max(const std::vector<double> &v);
double range(const std::vector<double> &v);
void centered(std::vector<double> &v);
void normalize_zscore(std::vector<double> &v);
} // namespace mathcore::stats