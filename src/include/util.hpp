#ifndef UTIL
#define UTIL
#include <limits>
#include <memory>
#include <cstdlib>
#include <cstdint>

using std::shared_ptr;
using std::make_shared;

//Constants

const double infinity   = std::numeric_limits<double>::infinity();
const double pi         = 3.14159265358979323846;

//functions

//random double between 0 and 1
inline double random_double(){
    return rand() / (RAND_MAX+1.0);
}

inline double random_double(double min, double max){
    return min + (max-min)*random_double();
}

//includes
#include "ray.hpp"
#include "glm.hpp"
#endif /* UTIL */
