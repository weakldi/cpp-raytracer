#include "util.hpp"





bool near_zero(glm::dvec3 in){
    const auto epsilon = 1e-8;
    return(fabs(in.x) < epsilon && fabs(in.y) < epsilon && fabs(in.z) < epsilon);
}

glm::dvec3 random_point_in_hemisphere(glm::dvec3 normal){
    glm::dvec3 vec = random_point_in_unit_sphere();
    if(glm::dot(vec,normal)> 0.0)
    {
        return vec;
    }
    return -vec;
}

std::ostream& operator<<(std::ostream& os, const glm::dvec3 vec) {
        os << "{" << vec.x << ", " << vec.y << ", " << vec.z <<"}";
        return os;
}