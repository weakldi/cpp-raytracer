#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "glm.hpp"

struct hit_record{
    double time;
    glm::dvec3 normal;
    glm::dvec3 point;
};

class hittable{
    public:
        virtual bool hit(const ray& ray, hit_record& hit_record) = 0;
};

#endif