#ifndef AABB_HPP
#define AABB_HPP

#include "hittable.hpp"
#include "glm.hpp"
#include "ray.hpp"

class aabb{
    public:
        aabb() = delete;
        aabb(const glm::dvec3& pos1, const glm::dvec3& pos2);
        bool hit(const ray& ray) const;
    public:
        // no trivial getter and setter methods!
        glm::dvec3 min; 
        glm::dvec3 max;
};

#endif /* aabb.h */
