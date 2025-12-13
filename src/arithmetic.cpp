#include <stdexcept>
#include "mathcore/arithmetic.hpp"

namespace mathcore::arithmetic{
    double divide(double a, double b)
    {
        if (b == 0){
            throw std::invalid_argument("Division by zero"); 
        }
        return a/b; 
    }

    double inverse(double a)
    {
        if (a == 0){
            throw std::invalid_argument("Division by zero!"); 
        }
        return 1.0/a; 
    }
} // namespace mathcore::arithmetic

