#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "glm.hpp"

class sphere : public hittable{
    public:
        sphere() = delete;
        sphere(const glm::dvec3& origin, const double radius)
            : m_orig(origin), m_radius(radius) {}

        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record);
    public:
        glm::dvec3 m_orig;
        double m_radius;
};

#endif