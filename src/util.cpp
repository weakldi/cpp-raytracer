#include "util.hpp"







glm::dvec3 random_point_in_hemisphere(glm::dvec3 normal){
    glm::dvec3 vec = random_point_in_unit_sphere();
    if(glm::dot(vec,normal)> 0.0)
    {
        return vec;
    }
    return -vec;
}

