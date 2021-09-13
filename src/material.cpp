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