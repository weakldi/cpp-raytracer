#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "glm.hpp"
#include "ray.hpp"
#include "material.hpp"

class sphere : public hittable{
    public:
        sphere() = delete;
        sphere(const glm::dvec3& origin, const double radius, shared_ptr<material> mat_ptr)
            : m_orig(origin), m_radius(radius), mat_ptr(mat_ptr) {}

        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override;
        virtual aabb bounding_box() const override;
    public:
        glm::dvec3 m_orig;
        double m_radius;
        shared_ptr<material> mat_ptr;
};


class s2 : public hittable{
    public:
        s2() = delete;
        s2(const glm::dvec3& origin, const double radius, shared_ptr<material> mat_ptr)
            : m_orig(origin), m_radius(radius), mat_ptr(mat_ptr) {}

        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const override;
        virtual aabb bounding_box() {return aabb({0,0,0}, {1,1,1});}
    public:
        glm::dvec3 m_orig;
        double m_radius;
        shared_ptr<material> mat_ptr;
};



#endif