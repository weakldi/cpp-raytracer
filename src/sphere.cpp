#include <iostream>
#include "sphere.hpp"

bool sphere::hit(const ray& ray,double t_min, double t_max, hit_record& hit_record) {
    /*
        C = center vector of sphere
        O = origin vector of ray
        t = time
        D = direction of ray
        R(t) = ray at t

        (R(t)-C) dot R(t)-C) = r*r = point on Sphere
        (O+t*D-C) dot (O+t*C-D) = r*r
        (t*D+(O-C)) dot (t*D+(O-C)) = r*r
        t*t*(D dot D) +2t D dot (O-C) + (O-C) dot (O-C) - r*r = 0

        a = (D dot D)
        b = 2* D dot (O-C)
        c = (O-C) dot (O-C) - r*r

        t_hit = -2 * (D dot (O-C)) +- sqrt(2 * (D dot (O-C))*2 * (D dot (O-C))-4*(D dot D)*r*r) / 2(D dot D)
        <=> t_hit = -(D dot (O-C)) +- sqrt((D dot (O-C))*(D dot (O-C))-(D dot D)*r*r) / (D dot D)
    */

    glm::dvec3 origin_to_center = ray.m_orig - m_orig;
    double b_half       = glm::dot(ray.m_dir, origin_to_center);
    double a            = glm::dot(ray.m_dir, ray.m_dir);
    double c            = glm::dot(origin_to_center, origin_to_center) - m_radius*m_radius;
    double dicriminant  = b_half*b_half - a*c;

    if(dicriminant > 0) //hit
    { 
        double sqrt_discriminant = glm::sqrt(dicriminant);

        double t_1 = (-b_half - sqrt_discriminant) / a;
        double t_2 = (-b_half + sqrt_discriminant) / a;
        std::cout << t_1 << " " << t_2 << " ";
        
        double t = t_1 < t_2 ? t_1 : t_2;
        if(t_1 < t_min || t_max < t_1)
        {
            if(t_2 < t_min || t_max < t_2){
                return false;
            }
            t = t_2;
        }
        glm::dvec3 hit_point = ray.at(t);
        glm::dvec3 normal = hit_point - m_orig ;

        //normalize normal. Since the hit is on the surface of the sphere
        // the lenght of the normal is the radius.
        hit_record.set_face_norlam( ray, normal / m_radius); 
        hit_record.point = hit_point;
        hit_record.time = t; 
        std::cout << std::endl;
        return true;
    }
    return false;
}