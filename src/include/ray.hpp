#ifndef RAY_H
#define RAY_H

#include "glm.hpp"

class ray{
    public:
        ray() {}
        ray(const glm::dvec3& origin, const glm::dvec3& direction)
            : m_orig(origin), m_dir(glm::normalize(direction)) {}

        glm::dvec3 at(double t) const {
            return m_orig + m_dir * t;
        }
    public:
        glm::dvec3 m_orig;
        glm::dvec3 m_dir;
};
#endif