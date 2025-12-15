#include "mathcore/stats.hpp"
#include "mathcore/arithmetic.hpp"

namespace mathcore::stats {
    double mean(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        return sum(v) / v.size(); 
    }

    // Two Pass Algorithm, à l'avenir flag et enum class pour le choix de l'algo. 
    double variance_population(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty");
        }
        double mu = mean(v); 
        double ssd = 0; 
        for (std::size_t i = 0; i < v.size(); i++){
            ssd += (v[i] - mu) * (v[i] - mu); 
        }
        return ssd / v.size(); 
    }

    double variance_sample(const std::vector<double>& v) {
        if (v.size() < 2){
            throw std::invalid_argument("Vector is empty or size 1");
        }
        double mu = mean(v); 
        double ssd = 0; 
        for (std::size_t i = 0; i < v.size(); i++){
            ssd += (v[i] - mu) * (v[i] - mu); 
        }
        return ssd / (v.size() - 1); 
    }

    double stddev(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty");
        }
        return std::sqrt(variance_population(v)); 
    }

    double sum(const std::vector<double>& v) {
        double sum = 0; 
        for (std::size_t i = 0; i < v.size(); i++) {
            sum += v[i]; 
        }
        return sum; 
    }

    double min(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        double m = v[0]; 
        for (std::size_t i = 1; i < v.size(); i++) {
            m = mathcore::arithmetic::min(v[i], m); 
        }
        return m; 
    }

    double max(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        double M = v[0]; 
        for (std::size_t i = 1; i < v.size(); i++) {
            M = mathcore::arithmetic::max(v[i], M); 
        }
        return M; 
    }

    double range(const std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        return max(v) - min(v); 
    }

    void centered(std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        double mu = mean(v); 
        for (std::size_t i = 0; i < v.size(); i++) {
            v[i] = v[i] - mu; 
        }
    }

    void normalize_zscore(std::vector<double>& v) {
        if (v.empty()){
            throw std::invalid_argument("Vector is empty"); 
        }
        double mu = mean(v); 
        double sigma = stddev(v); 
        if (sigma == 0) {
            // tous les éléments deviennent 0
            for (auto& x : v) x = 0.0;
            return;
}
        for (std::size_t i = 0; i < v.size(); i++) {
            v[i] = (v[i] - mu) / sigma; 
        }
    } 
} //namespace mathcore::stats