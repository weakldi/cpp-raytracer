#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "glm.hpp"

class sphere : public hittable{
    public:
        sphere() = delete;
        sphere(const glm::dvec3& origin, const double radius)
            : orig(origin), r(radius) {}

        virtual bool hit(const ray& ray, hit_record& hit_record);
    public:
        glm::dvec3 orig;
        double r;
};

#endif