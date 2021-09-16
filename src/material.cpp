#include "material.hpp"
#include "hittable.hpp"

bool diffuse::scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const{
    auto scatter_vec = record.normal + random_point_in_hemisphere(record.normal);
    if(near_zero(scatter_vec)){
        scatter_vec =  record.normal;
    }
    scattered = ray(record.point,scatter_vec);
    color = this->color;
    return true;
}

bool metal::scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const{
    auto scatter_vec = reflect(glm::normalize(ray_in.m_dir), record.normal);

    scattered = ray(record.point,scatter_vec+ fuzz*random_point_in_unit_sphere());
    color = this->color;
    return glm::dot(scatter_vec, record.normal) > 0;
}

double reflectance_slick(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

bool dielectric::scatter(const ray& ray_in, const hit_record& record, glm::dvec3& color, ray& scattered) const{
    
    auto ray_dir_normalized = glm::normalize(ray_in.m_dir);
    double cos_theta = fmin(glm::dot(-ray_dir_normalized, record.normal),1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    double refraction_ratio = record.front_face? (1.0/ir) : ir;
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;

    glm::dvec3 scatter_ray;
    if(cannot_refract || reflectance_slick(cos_theta,refraction_ratio) > random_double())
    {
        scatter_ray = reflect(ray_dir_normalized,record.normal);
    }
    else
    {
        scatter_ray = refract(ray_dir_normalized, record.normal,refraction_ratio);
    }

     

    scattered = ray(record.point,scatter_ray);
    color = this->color;
    return true;
}