#ifndef UTIL
#define UTIL
#include <limits>
#include <memory>


using std::shared_ptr;
using std::make_shared;

//Constants

const double infinity   = std::numeric_limits<double>::infinity();
const double pi         = 3.14159265358979323846;

//includes
#include "ray.hpp"
#include "glm.hpp"
#endif /* UTIL */
