#ifndef VECTOR_UTIL
#define VECTOR_UTIL

#include "glm.hpp"

using glm::dvec3;
using glm::dot;

inline dvec3 reflect(const dvec3& in, const dvec3& normal){
    return in - 2* dot(in,normal)*normal;
}

inline dvec3 refract(const dvec3& in, const dvec3& normal, double refraction_index){
    auto cos_theta = fmin(dot(-in,normal), 1.0);
    dvec3 r_out_perp = refraction_index * (in + cos_theta*normal);
    dvec3 r_out_parallel = -sqrt(fabs(1.0 - dot(r_out_perp,r_out_perp)))*normal;
    return r_out_perp + r_out_parallel;
}

#endif /* VECTOR_UTIL */
