#ifndef HITTABLE
#define HITTABLE

#include <iostream>

#include "ray.hpp"
#include "glm.hpp"
#include "material.hpp"

struct hit_record{
    double time;
    glm::dvec3 normal;
    glm::dvec3 point;
    bool front_face;
    shared_ptr<material> mat_ptr;

    inline void set_face_norlam(const ray& ray, const glm::dvec3& outward_normal) 
    {
        front_face = glm::dot(ray.m_dir,outward_normal) < 0;
        
        if(front_face)
        {
            normal = outward_normal;
        }
        else
        {
            normal = -outward_normal;
        }
    }
};

class hittable{
    public:
        virtual bool hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) const = 0;
};

#endif /* HITTABLE */
